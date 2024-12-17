/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:43:13 by smercado          #+#    #+#             */
/*   Updated: 2024/12/17 13:17:25 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_argument(t_lex **list_lex, t_lex **cur_lex )
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
	if (tmp_list->terminated)
		return (1);
	return (0);
}

static void	print_type(t_lex_type e)
{
	if (e == UNSET)
		printf("type: UNSET\n");
	if (e == PRINCIPAL_WORD)
		printf("type: PRINCIPAL_WORD\n");
	if (e == REDIRECTION)
		printf("type: REDIRECTION\n");
	if (e == PIP)
		printf("type: PIP\n");
}

void	lex_debug(t_lex *lex)
{
	int i = 1;
	int	j;
	while (lex)
	{
		j = 0;
		printf("Nodo %d\n", i);
		print_type(lex->type);
		printf("comando numero: %d\n", lex->command_num); 
		printf("command: %s\n", lex->command);
		print_operator(lex->redir_type);
		if (lex->arguments)
		{
			while (lex->arguments[j])
			{	
				printf("argument[%d]: %s\n", j, lex->arguments[j]);
				j++;
			}
		}
		printf("\n");
		i++;
		lex = lex->next;
	}
}
