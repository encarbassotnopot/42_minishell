/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:43:13 by smercado          #+#    #+#             */
/*   Updated: 2024/12/18 12:29:02 by smercado         ###   ########.fr       */
/*   Updated: 2024/12/18 09:26:34 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_argument(t_lex **list_lex, t_lex **cur_lex)
{
	t_lex	*tmp_list;

	tmp_list = *list_lex;
	while (tmp_list)
	{
		if (tmp_list->type == PRINCIPAL_WORD && \
			(*cur_lex)->command_num == tmp_list->command_num)
			break ;
		tmp_list = tmp_list->next;
	}
	if (tmp_list)
	{
		if (tmp_list->type == PRINCIPAL_WORD && \
			(*cur_lex)->command_num == tmp_list->command_num)
			return (1);
	}
	return (0);
}

int	is_terminated(t_token *token, t_token *list_tok)
{
	t_token	*tmp_list;

	tmp_list = list_tok;
	if (token == list_tok)
		return (1);
	while (tmp_list->next && tmp_list)
	{
		if (token == tmp_list->next)
			break ;
		tmp_list = tmp_list->next;
	}
	if (tmp_list->terminated || (tmp_list->type == OPERATOR && \
		!tmp_list->char_buf))
		return (1);
	return (0);
}

int	is_word(t_token *token)
{
	if (token->type == WORD || token->type == DQUOTE || token->type == QUOTE)
		return (1);
	return (0);
}

t_lex	*make_new_lex(t_lex *lex, int *cmd_num)
{
	t_lex	*my_lex;

	my_lex = ft_calloc(1, sizeof(t_lex));
	my_lex->command = NULL;
	my_lex->command_num = *cmd_num;
	if (lex)
		lex->next = my_lex;
	return (my_lex);
}