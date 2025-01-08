/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smercado <smercado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:37:26 by ecoma-ba          #+#    #+#             */
/*   Updated: 2025/01/08 18:04:56 by smercado         ###   ########.fr       */
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
int	run_env(t_shell *sh)
{
	t_environment	*env;

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
int	run_exit(t_shell *sh)
{
	int	arg_count;

	arg_count = count_args(sh->command);
	if (arg_count > 2)
	{
		printf("minishell: exit: too many arguments\n");
		cleanup(sh, NULL, EXIT_FAILURE);
	}
	if (arg_count == 1)
	{
		cleanup(sh, NULL, 0);
		return (EXIT_SUCCESS);
	}
	if (!is_numeric(sh->command->arguments[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n",
			sh->command->arguments[1]);
		cleanup(sh, NULL, EXIT_FAILURE);
	}
	cleanup(sh, NULL, ft_atoi(sh->command->arguments[1]));
	return (0);
}
