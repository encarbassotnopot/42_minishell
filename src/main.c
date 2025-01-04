/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:12:52 by smercado          #+#    #+#             */
/*   Updated: 2025/01/04 12:31:45 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "execution.h"
#include "minishell.h"
#include "parsing.h"

/**
 * Parses a line into a command list. Returns NULL on error.
 */
t_command	*parse_line(t_shell *shinfo, char *line)
{
	t_token		*tokens;
	t_lex		*lex;
	t_command	*cmd;

	if (!line || ft_isspace_str(line))
	{
		free(line);
		return (NULL);
	}
	add_history(line);
	tokens = tokenization(line);
	free(line);
	expand_tokens(tokens, shinfo->env);
	lex = redefine_token_lex(tokens);
	free_tokens(&tokens);
	if (checker_lex(lex) == 1)
		cmd = redefine_lex(lex);
	else
		cmd = NULL;
	free_lex_list(&lex);
	return (cmd);
}

/**
 * Cleansup everityhing in the shinfo struct.
 * Prints the given exit message and extits with the given status code.
 */
void	cleanup(t_shell *shinfo, char *msg, int status)
{
	free_comandes(&shinfo->command);
	free_env(&shinfo->env);
	rl_clear_history();
	ft_putstr_fd(msg, STDOUT_FILENO);
	exit(status);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_shell	shinfo;

	shinfo.command = NULL;
	shinfo.exit = 0;
	shinfo.env = init_env(envp);
	init_signals();
	while (1312)
	{
		line = readline("minishell $> ");
		if (!line)
			cleanup(&shinfo, "exit\n", 0);
		shinfo.command = parse_line(&shinfo, line);
		if (!shinfo.command)
			continue ;
		else if ((shinfo.command->arguments && shinfo.command->arguments[0])
			|| (shinfo.command->file && shinfo.command->file[0]))
			shinfo.exit = run_commands(shinfo.command, shinfo.env);
		free_comandes(&shinfo.command);
		signal(SIGQUIT, SIG_IGN);
	}
	cleanup(&shinfo, NULL, 0);
}
