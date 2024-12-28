/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smercado <smercado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:43:13 by smercado          #+#    #+#             */
/*   Updated: 2024/12/28 12:32:19 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Checks if cur_lex is an argument. It iterates through the lex list,
 * looking for the command_num and principal word.
 * If it finds it, it means it's an argument and returns 1.
 * Otherwise, it returns 0.
 */
int	is_argument(t_lex **list_lex, t_lex **cur_lex)
{
	t_lex	*tmp_list;

	tmp_list = *list_lex;
	while (tmp_list)
	{
		if (tmp_list->type == PRINCIPAL_WORD
			&& (*cur_lex)->command_num == tmp_list->command_num)
			break ;
		tmp_list = tmp_list->next;
	}
	if (tmp_list)
	{
		if (tmp_list->type == PRINCIPAL_WORD
			&& (*cur_lex)->command_num == tmp_list->command_num)
			return (1);
	}
	return (0);
}

/**
 * Checks if the given token is terminated, based on
 * the previous token in the token list.
 * Returns 1 if the token is terminated, otherwise 0.
 */
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
	if (tmp_list->terminated || (tmp_list->type == OPERATOR
			&& !tmp_list->char_buf))
		return (1);
	return (0);
}

/**
 * Checks if the token is a word, a double quote, or a single quote.
 * Returns 1 if the token is one of these types, otherwise 0.
 */
int	is_word(t_token *token)
{
	if (token->type == WORD || token->type == DQUOTE || token->type == QUOTE)
		return (1);
	return (0);
}

/**
 * Creates and returns a new lex node.
 */
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

int	checker_lex(t_lex *lex)
{
	t_lex	*tmp_lex;

	tmp_lex = lex;
	while (tmp_lex)
	{
		if (tmp_lex->type == REDIRECTION)
		{
			if (!tmp_lex->command)
			{
				parse_error("parse error near `n'");
				return (0);
			}
		}
		else if (tmp_lex->type == PIP)
		{
			if (!tmp_lex->next)
			{
				parse_error("parse error near `|'");
				return (0);
			}
		}
		tmp_lex = tmp_lex->next;
	}
	return (1);
}