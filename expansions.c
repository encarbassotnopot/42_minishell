/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:52:22 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/12/03 13:29:54 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 *	Returns the next environment variable.
 *	Advances the str pointer until the end of the variable.
 *	Returns and sets str to NULL if not found.
 */
char	*get_next_var(char *str)
{
	size_t	len;
	char	*var;

	len = 0;
	if (!*str)
		return (NULL);
	while (ft_isalnum(str[len]) || str[len] == '_')
		len++;
	var = ft_calloc(len + 1, sizeof(char));
	ft_strlcpy(var, str, len+1);
	return (var);
}

void	expand_tokens(t_token *const token)
{
	t_token	*tok;
	char	*var;
	char	*str;

	tok = token;
	while (tok)
	{
		str = tok->char_buf;
		if (tok->type == WORD || tok->type == DQUOTE)
			while (ft_strchr(str, '$'))
			{
				str = ft_strchr(str, '$') + 1;
				var = get_next_var(str);
				printf("test: found var $%s:%s\n", var, getenv(var));
			}
		tok = tok->next;
	}
}
