/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:52:22 by ecoma-ba          #+#    #+#             */
/*   Updated: 2025/01/08 13:08:07 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "parsing.h"

char	*get_var_text(char *name, t_environment *env, t_shell *shinfo)
{
	if (ft_strcmp(name, "?") == 0)
		return (shinfo->exit);
	return ((char *)get_const_env_value(env, name));
}

void	recreate_charbuf(t_token *const tok, t_environment *env,
		t_shell *shinfo)
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
			fragments[++i] = get_var_text(var, env, shinfo);
			fragments[++i] = tok->char_buf;
			free(var);
		}
		else
			tok->char_buf++;
	}
	tok->char_buf = ft_concatenate(fragments);
	free(fragments);
}

void	expand_tokens(t_token *const token, t_environment *env, t_shell *shinfo)
{
	t_token	*tok;
	char	*old_buf;

	tok = token;
	while (tok)
	{
		if (tok->type == WORD || tok->type == DQUOTE)
		{
			old_buf = tok->char_buf;
			recreate_charbuf(tok, env, shinfo);
			free(old_buf);
		}
		tok = tok->next;
	}
}
