/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   estructura_intermedia.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:06:14 by smercado          #+#    #+#             */
/*   Updated: 2024/12/19 14:26:03 by smercado         ###   ########.fr       */
/*   Updated: 2024/12/18 09:03:41 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	append_args(t_token *tok, t_lex **cur_lex, t_lex **l_lex)
{
	t_lex	*tmp;

	tmp = *l_lex;
	while (tmp)
	{
		if (tmp->type == PRINCIPAL_WORD && \
			(*cur_lex)->command_num == tmp->command_num)
			break ;
		tmp = tmp->next;
	}
	if (!tmp->arguments)
		append_new_argument(tok, tmp);
	else
		append_next_argument(tmp, tok);
}

void	manage_started_words(t_lex **cur_lex, t_lex **list_lex, \
		t_token *token, int *comand_num)
{
	if ((*cur_lex)->redir_type == OP_UNSET && (!(*cur_lex)->arguments))
		append_first_word(token, cur_lex, comand_num);
	else
		append_started_argument(list_lex, cur_lex, token);
}

void	manage_words(t_token *token, t_lex **cur_lex, t_lex **list_lex, \
		int *comand_num)
{
	if (is_argument(list_lex, cur_lex))
		append_args(token, cur_lex, list_lex);
	else
		append_first_word(token, cur_lex, comand_num);
}

void	manage_operators(t_token *token, t_lex **cur_lex, int *comand_num)
{
	if ((*cur_lex) && (*cur_lex)->type != UNSET)
		*cur_lex = make_new_lex(*cur_lex, comand_num);
	if (token->oper != PIPE)
	{
		(*cur_lex)->type = REDIRECTION;
		(*cur_lex)->redir_type = token->oper;
	}
	else
	{
		(*cur_lex)->type = PIP;
		(*comand_num)++;
		if (token->next)
			*cur_lex = make_new_lex(*cur_lex, comand_num);
	}
}

t_lex	*redefine_token_lex(t_token *token)
{
	t_lex	*cur_lex;
	t_lex	*list_lex;
	t_token	*list_tok;
	int		comand_num;

	comand_num = 1;
	list_lex = make_new_lex(NULL, &comand_num);
	cur_lex = list_lex;
	list_tok = token;
	while (token)
	{
		if (is_word(token) && cur_lex->type != REDIRECTION)
		{
			if (is_terminated(token, list_tok))
				manage_words(token, &cur_lex, &list_lex, &comand_num);
			else
				manage_started_words(&cur_lex, &list_lex, token, &comand_num);
		}
		else if (token->type == OPERATOR)
			manage_operators(token, &cur_lex, &comand_num);
		else
			append_redirection_word(token, &cur_lex, &list_tok, &list_lex);
		token = token->next;
	}
	free_tokens(list_tok);
	return (list_lex);
}
