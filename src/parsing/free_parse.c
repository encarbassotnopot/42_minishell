/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:30:34 by smercado          #+#    #+#             */
/*   Updated: 2025/01/03 15:55:06 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_tokens(t_token *tokens)
{
	t_token	*old_t;

	while (tokens)
	{
		old_t = tokens;
		tokens = tokens->next;
		free(old_t->char_buf);
		free(old_t);
	}
}

/**
 * Frees the memory of a lex node, including its command and arguments.
 */
void	free_lex_node(t_lex *node)
{
	int	i;

	i = 0;
	if (node->command)
		free(node->command);
	if (node->arguments)
	{
		while (node->arguments[i])
		{
			free(node->arguments[i]);
			i++;
		}
		free(node->arguments);
	}
	free(node);
}

void	free_lex_list(t_lex *list_lex)
{
	t_lex *temp;

	while (list_lex)
	{
		temp = list_lex;
		list_lex = list_lex->next;
		free_lex_node(temp);
	}
}