/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comandes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:29:03 by smercado          #+#    #+#             */
/*   Updated: 2025/01/08 13:59:56 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Iterates through the lex list and creates commands with all combined:
 * argument array, redirections and files.
 * If a pipe is encountered, a new command is created.
 */
t_command	*redefine_lex(t_lex *list_lex)
{
	t_command	*cur_com;
	t_command	*list_com;
	t_lex		*cur_lex;

	cur_lex = list_lex;
	list_com = make_new_command(NULL, get_arg_size(cur_lex),
			get_redir_size(cur_lex));
	cur_com = list_com;
	add_word(cur_lex, cur_com);
	while (cur_lex)
	{
		if (cur_lex->type == PIP)
		{
			cur_com = make_new_command(cur_com, get_arg_size(cur_lex->next),
					get_redir_size(cur_lex->next));
			add_word(cur_lex->next, cur_com);
		}
		else if (cur_lex->redir_type != OP_UNSET)
			add_redirection(cur_lex, cur_com);
		cur_lex = cur_lex->next;
	}
	return (list_com);
}
