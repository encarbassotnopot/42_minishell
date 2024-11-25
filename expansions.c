/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:52:22 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/11/25 14:03:09 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 *	Returns the next environment variable.
 *	Advances the str pointer until the end of the variable.
 *	Returns and sets str to NULL if not found.
 */
char	*get_next_var(char **str)
{
	size_t	len;

	len = 0;
	*str = ft_strchr(*str, '$');
	*str++;
	if (!*str )
		return (NULL);
	while (ft_isalnum((*str)[len]) || (*str)[len] == '_')
		len++;
	printf("test: %*s", len, str);
}

void	expand_tokens(t_token *const token)
{
	t_token	*tok;
	char	*var;

	tok = token;
	while (tok)
	{
		if (tok->type == WORD || tok->type == DQUOTE)
			while (ft_strchr(tok->char_buf, '$'))
			{
			}
		tok = tok->next;
	}
}
