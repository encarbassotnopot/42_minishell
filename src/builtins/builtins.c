/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:22:34 by ecoma-ba          #+#    #+#             */
/*   Updated: 2025/01/09 13:19:08 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/**
 * Checks if the given command is a "raw builtin".
 * A raw builtin is a builtin that has to be run on the parent process.
 */
bool	is_raw_builtin(t_command *command)
{
	char	*name;

	if (!command->arguments)
		return (false);
	name = command->arguments[0];
	if (ft_strcmp(name, "cd") == 0)
		return (true);
	if (ft_strcmp(name, "export") == 0)
		return (true);
	if (ft_strcmp(name, "unset") == 0)
		return (true);
	if (ft_strcmp(name, "exit") == 0)
		return (true);
	return (false);
}

/**
 * Checks if the given command is a builtin.
 */
bool	is_builtin(t_command *command)
{
	char	*name;

	if (!command->arguments)
		return (false);
	name = command->arguments[0];
	if (ft_strcmp(name, "cd") == 0)
		return (true);
	if (ft_strcmp(name, "export") == 0)
		return (true);
	if (ft_strcmp(name, "unset") == 0)
		return (true);
	if (ft_strcmp(name, "exit") == 0)
		return (true);
	if (ft_strcmp(name, "echo") == 0)
		return (true);
	if (ft_strcmp(name, "env") == 0)
		return (true);
	if (ft_strcmp(name, "pwd") == 0)
		return (true);
	return (false);
}

/**
 * Checks if the given command is a builtin.
 */
int	(*get_builtin(t_command *command))(t_shell *sh, t_command *command)
{
	char	*name;

	if (!command->arguments)
		return (NULL);
	name = command->arguments[0];
	if (ft_strcmp(name, "cd") == 0)
		return (run_cd);
	if (ft_strcmp(name, "export") == 0)
		return (run_export);
	if (ft_strcmp(name, "unset") == 0)
		return (run_unset);
	if (ft_strcmp(name, "exit") == 0)
		return (run_exit);
	if (ft_strcmp(name, "echo") == 0)
		return (run_echo);
	if (ft_strcmp(name, "env") == 0)
		return (run_env);
	if (ft_strcmp(name, "pwd") == 0)
		return (run_pwd);
	return (NULL);
}

int	run_builtin(t_shell *shinfo, t_command *command)
{
	int	(*builtin)(t_shell *, t_command *);

	builtin = get_builtin(command);
	if (builtin)
		return ((*builtin)(shinfo, command));
	else
		return (0);
}
