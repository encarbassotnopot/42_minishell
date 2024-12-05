/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smercado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:43:13 by smercado          #+#    #+#             */
/*   Updated: 2024/12/05 14:43:30 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		printf("comando numero: %d\n", lex->comand_num); 
		printf("comand: %s\n", lex->comand);
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
