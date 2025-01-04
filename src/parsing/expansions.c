/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:52:22 by ecoma-ba          #+#    #+#             */
/*   Updated: 2025/01/04 12:36:51 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "parsing.h"

/**
 *	Counts the environment variable's name's len.
 *	*str is a pointer to the start of the variable name (not including the '$')
 */
size_t	get_var_len(char *str)
{
	size_t	len;

	len = 0;
	while (ft_isalnum(str[len]) || str[len] == '_')
		len++;
	return (len);
}

/**
 *	Returns the next environment variable or NULL if not found (or malformed).
 */
char	*get_next_var(char *str)
{
	size_t	len;
	char	*var;

	len = get_var_len(str);
	if (!len)
		return (NULL);
	var = ft_calloc(len + 1, sizeof(char));
	ft_strlcpy(var, str, len + 1);
	return (var);
}

unsigned int	var_count(char *str)
{
	unsigned int	count;
	size_t			i;

	if (!str)
		return (0);
	count = 0;
	i = -1;
	while (str[++i])
		if (str[i] == '$')
			count++;
	return (count);
}

void	recreate_charbuf(t_token *const tok, t_environment *env)
{
	char			*var;
	char			**fragments;
	unsigned int	i;

	fragments = ft_calloc(2 + var_count(tok->char_buf) * 2, sizeof(char *));
	i = -1;
	fragments[++i] = tok->char_buf;
	while (ft_strchr(tok->char_buf, '$'))
	{
		tok->char_buf = ft_strchr(tok->char_buf, '$');
		var = get_next_var(tok->char_buf + 1);
		if (var)
		{
			*tok->char_buf = '\0';
			tok->char_buf += 1 + get_var_len(tok->char_buf + 1);
			fragments[++i] = get_const_env_value(env, var);
			fragments[++i] = tok->char_buf;
			free(var);
		}
		else
			tok->char_buf++;
	}
	tok->char_buf = ft_concatenate(fragments);
	free(fragments);
}

void	expand_tokens(t_token *const token, t_environment *env)
{
	t_token	*tok;
	char	*old_buf;

	tok = token;
	while (tok)
	{
		if (tok->type == WORD || tok->type == DQUOTE)
		{
			old_buf = tok->char_buf;
			recreate_charbuf(tok, env);
			free(old_buf);
		}
		tok = tok->next;
	}
}
