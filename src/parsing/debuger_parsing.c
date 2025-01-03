/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debuger_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:26:46 by smercado          #+#    #+#             */
/*   Updated: 2025/01/03 16:54:27 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

void	print_operator(t_operator_type e)
{
	if (e == OP_UNSET)
		printf("type: OP_UNSET\n");
	if (e == LESS)
		printf("type: LESS <\n");
	if (e == GREAT)
		printf("type: GREAT >\n");
	if (e == DLESS)
		printf("type: DLESS <<\n");
	if (e == DGREAT)
		printf("type: DGREAT >>\n");
	if (e == PIPE)
		printf("type: PIPE |\n");
}

void	print_operator_line(t_operator_type e)
{
	if (e == LESS)
		printf("<");
	if (e == GREAT)
		printf(">");
	if (e == DLESS)
		printf("<<");
	if (e == DGREAT)
		printf(">>");
	if (e == PIPE)
		printf("|");
}

void	print_tok_type(t_token_type e)
{
	if (e == TYPE_UNSET)
		printf("type: TYPE_UNSET\n");
	if (e == WORD)
		printf("type: WORD\n");
	if (e == OPERATOR)
		printf("type: OPERATOR\n");
	if (e == QUOTE)
		printf("type: QUOTE\n");
	if (e == DQUOTE)
		printf("type: DQUOTE\n");
}

void	tok_debug(t_token *t)
{
	while (t)
	{
		print_tok_type(t->type);
		printf("chbuf: %s\n", t->char_buf);
		print_operator(t->oper);
		printf("terminated?: %i\n\n", t->terminated);
		t = t->next;
	}
}

void	tok_debug_line(t_token *t)
{
	printf("line: ");
	while (t)
	{
		if (t->type == OPERATOR)
		{
			printf(RED);
			print_operator_line(t->oper);
		}
		if (t->type == QUOTE)
			printf(GREEN);
		if (t->type == DQUOTE)
			printf(BLUE);
		if (t->type && t->char_buf)
			printf("%s", t->char_buf);
		printf(RESET);
		if (t->terminated)
			printf(" ");
		t = t->next;
	}
	printf("\n\n");
}
static void	print_lex_type(t_lex_type e)
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
		print_lex_type(lex->type);
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
				print_operator(command->redir[j]);
				printf("file: %s\n", command->file[j]);
				j++;
			}
		}
		command = command->next;
		i++;
	}
}
