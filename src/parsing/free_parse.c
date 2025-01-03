/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:30:34 by smercado          #+#    #+#             */
/*   Updated: 2025/01/03 17:18:46 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_tokens(t_token **tokens)
{
	t_token	*my_t;
	t_token	*old_t;

	if (!*tokens)
		return ;
	my_t = *tokens;
	while (my_t)
	{
		old_t = my_t;
		my_t = my_t->next;
		free(old_t->char_buf);
		free(old_t);
	}
	*tokens = NULL;
}

/**
 * Frees the memory of a lex node, including its command and arguments.
 */
void	free_lex_node(t_lex **node)
{
	int		i;
	t_lex	*my_node;

	if (!node)
		return ;
	my_node = *node;
	i = 0;
	if (my_node->command)
		free(my_node->command);
	if (my_node->arguments)
	{
		while (my_node->arguments[i])
		{
			free(my_node->arguments[i]);
			i++;
		}
		free(my_node->arguments);
	}
	free(my_node);
	*node = NULL;
}

void	free_lex_list(t_lex **list_lex)
{
	t_lex *my_list_lex;
	t_lex *temp;

	if (!list_lex)
		return ;
	my_list_lex = *list_lex;
	while (my_list_lex)
	{
		temp = my_list_lex;
		my_list_lex = my_list_lex->next;
		free_lex_node(&temp);
	}
	*list_lex = NULL;
}