/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debuger_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smercado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:26:46 by smercado          #+#    #+#             */
/*   Updated: 2024/12/18 13:06:04 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
	int	i;
	int	j;

	i = 1;
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

void	command_debug(t_command *command)
{
	int	i;
	int	j;

	i = 1;
	while (command)
	{
		j = 0;
		printf("\ncomanda %d\n", i);
		if (command->arguments)
		{
			while (command->arguments[j])
			{
				printf("argument[%d]: %s\n", j, command->arguments[j]);
				j++;
			}
		}
		if (command->file)
		{
			j = 0;
			while (command->file[j])
			{
				print_operator(*command->redir[j]);
				printf("file: %s\n", command->file[j]);
				j++;
			}
		}
		command = command->next;
		i++;
	}
}
