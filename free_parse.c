/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:30:34 by smercado          #+#    #+#             */
/*   Updated: 2025/01/02 16:17:23 by ecoma-ba         ###   ########.fr       */
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
		free_comanda(tmp_com);
		command = command->next;
		free(tmp_com);
	}
}

void	free_strarr(char **str)
{
	int i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}