/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:12:52 by smercado          #+#    #+#             */
/*   Updated: 2024/12/27 09:55:11 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
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

void	print_type(t_token_type e)
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
		print_type(t->type);
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

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_token			*tokens;
	t_lex			*lex;
	t_command		*command;
	pid_t			ex;
	t_environment	*env;

	env = init_env(envp);
	print_env(env);
	init_signals();
	while (1)
	{
		line = readline("minishell_test: ");
		if (line)
		{
			add_history(line);
			tokens = tokenization(line);
			free(line);
			expand_tokens(tokens);
			lex = redefine_token_lex(tokens);
			// lex_debug(lex);
			command = redefine_lex(lex);
			// command_debug(command);
			if (command)
			{
				ex = run_commands(command, envp);
				waitpid(ex, 0, 0);
			}
			free_comandes(command);
		}
		else
		{
			// detectat Ctrl+D
			if (line == NULL)
			{
				printf("exit\n");
				rl_clear_history();
				exit(0);
			}
		}
	}
	rl_clear_history();
	exit(0);
}
