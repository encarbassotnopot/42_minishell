/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:12:52 by smercado          #+#    #+#             */
/*   Updated: 2025/01/08 10:06:45 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "execution.h"
#include "minishell.h"
#include "parsing.h"

/**
 * Returns 1 if the given command is empty, 0 otherwise.
 */
int	check_empty_cmd(t_command *command)
{
	if (command->arguments && command->arguments[0])
		return (0);
	if (command->file && command->file[0])
		return (0);
	return (1);
}

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
	expand_tokens(tokens, shinfo->env, shinfo);
	lex = redefine_token_lex(tokens);
	free_tokens(&tokens);
	if (checker_lex(lex) == 1)
	{
		cmd = redefine_lex(lex);
		if (check_empty_cmd(cmd))
			free_comandes(&cmd);
	}
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
	cmd_fd_close(shinfo->command);
	free_comandes(&shinfo->command);
	free_env(&shinfo->env);
	free(shinfo->exit);
	rl_clear_history();
	ft_putstr_fd(msg, STDOUT_FILENO);
	exit(status);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_shell	shinfo;
	int		exit;

	(void)argc;
	(void)argv;
	shinfo.command = NULL;
	shinfo.exit = NULL;
	shinfo.env = init_env(envp);
	exit = 0;
	init_signals();
	while (1312)
	{
		free(shinfo.exit);
		shinfo.exit = ft_itoa(exit);
		line = readline("minishell $> ");
		if (!line)
			cleanup(&shinfo, "exit\n", 0);
		shinfo.command = parse_line(&shinfo, line);
		if (!shinfo.command)
			continue ;
		exit = run_commands(shinfo.command, shinfo.env, &shinfo);
		if (WIFEXITED(exit))
			exit = WEXITSTATUS(exit);
		else
			exit = -161;
		free_comandes(&shinfo.command);
		signal(SIGQUIT, SIG_IGN);
	}
	cleanup(&shinfo, NULL, 0);
}
