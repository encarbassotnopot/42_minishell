/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:52:22 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/12/05 11:46:00 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	expand_tokens(t_token *const token)
{
	t_token			*tok;
	char			*var;
	char			*str;
	char			**fragments;
	unsigned int	i;

	tok = token;
	while (tok)
	{
		str = tok->char_buf;
		fragments = ft_calloc(2 + var_count(str) * 2, sizeof(char *));
		if (tok->type == WORD || tok->type == DQUOTE)
		{
			i = -1;
			fragments[++i] = str;
			while (ft_strchr(str, '$'))
			{
				str = ft_strchr(str, '$');
				var = get_next_var(str + 1);
				if (var)
				{
					*str = '\0';
					str += 1 + get_var_len(str + 1);
					fragments[++i] = getenv(var);
					if (!fragments[i])
						i--;
					fragments[++i] = str;
					free(var);
				}
				str++;
			}
			printf("%s\n", ft_concatenate(fragments));
		}
		tok = tok->next;
	}
}
