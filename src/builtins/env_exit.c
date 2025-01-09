/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:37:26 by ecoma-ba          #+#    #+#             */
/*   Updated: 2025/01/09 13:07:09 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * Prints the whole environment.
 */
int	run_env(t_shell *sh, t_command *command)
{
	t_environment	*env;

	(void)command;
	env = sh->env;
	while (env)
	{
		printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return (0);
}

/**
 * Exits the shell (or the child process).
 */
int	run_exit(t_shell *sh, t_command *command)
{
	int	arg_count;

	arg_count = count_args(command);
	if (arg_count > 2)
	{
		printf("minishell: exit: too many arguments\n");
		cleanup(sh, NULL, EXIT_FAILURE);
	}
	if (arg_count == 1)
	{
		cleanup(sh, NULL, 0);
	}
	if (!is_numeric(command->arguments[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n",
			command->arguments[1]);
		cleanup(sh, NULL, EXIT_FAILURE);
	}
	cleanup(sh, NULL, ft_atoi(command->arguments[1]));
	return (0);
}
