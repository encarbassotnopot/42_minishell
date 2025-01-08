/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:12:52 by smercado          #+#    #+#             */
/*   Updated: 2025/01/08 15:52:40 by ecoma-ba         ###   ########.fr       */
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
	free_comandes(&shinfo->command);
	free_env(&shinfo->env);
	free(shinfo->exit);
	rl_clear_history();
	ft_putstr_fd(msg, STDOUT_FILENO);
	exit(status);
}

void	init_shinfo(t_shell *shinfo, char **envp)
{
	shinfo->command = NULL;
	shinfo->exit = NULL;
	shinfo->env = init_env(envp);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_shell	shinfo;
	int		exit;

	(void)argc;
	(void)argv;
	init_shinfo(&shinfo, envp);
	exit = 0;
	while (1312)
	{
		interactive_signals();
		free(shinfo.exit);
		shinfo.exit = ft_itoa(exit);
		line = readline("minishell $> ");
		if (!line)
			cleanup(&shinfo, "exit\n", 0);
		non_interactive_signals();
		shinfo.command = parse_line(&shinfo, line);
		if (!shinfo.command)
			continue ;
		exit = run_commands(shinfo.command, shinfo.env, &shinfo);
		free_comandes(&shinfo.command);
	}
	cleanup(&shinfo, NULL, 0);
}
