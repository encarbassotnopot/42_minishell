/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smercado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:30:34 by smercado          #+#    #+#             */
/*   Updated: 2024/12/19 14:40:54 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_tokens(t_token *tokens)
{
	t_token *old_t;

	while (tokens)
	{
		old_t = tokens;
		tokens = tokens->next;
		free(old_t->char_buf);
		free(old_t);
	}
}

void	free_lex_list(t_lex *list_lex)
{
	t_lex	*temp;

	while (list_lex)
	{
		temp = list_lex;
		list_lex = list_lex->next;
		free_lex_node(temp);
	}
}

void	free_comandes(t_command *command)
{
	t_command	*tmp_com;

	while (command)
	{
		tmp_com = command;
		free_cmd_node(tmp_com);
		command = command->next;
		free(tmp_com);
	}
}
