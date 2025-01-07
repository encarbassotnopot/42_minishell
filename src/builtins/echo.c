/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smercado <smercado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:43:34 by smercado          #+#    #+#             */
/*   Updated: 2025/01/07 12:17:13 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

int	run_unset(t_command *command, t_environment *env)
{
	int	arg_count;
	int	i;

	i = 1;
	arg_count = count_args(command);
	if (arg_count < 1)
		return (0);
	while (arg_count >= i)
	{
		if (get_env_value(env, command->arguments[i])
			unset_env_value(env, command->arguments[i]);
	}
	return (0);
}

int	run_echo(t_command *command, t_environment *env)
{
	int	arg_count;
	int	i;

	i = 1;
	arg_count = count_args(command);
	void(env);
	if (arg_count == 1)
		printf("\n");
	else if (ft_strcmp(command->arguments[1], "-n") == 0)
	{
		while (arg_count - 2 > i++)
			printf("%s ", command->arguments[i]);
		printf("%s", command->arguments[i]);
	}
	else
	{
		while (arg_count - 1 > i)
		{
			printf("%s ", command->arguments[i]);
			i++;
		}
		printf("%s\n", command->arguments[i]);
	}
	return (0);
}
