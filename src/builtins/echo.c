/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:43:34 by smercado          #+#    #+#             */
/*   Updated: 2025/01/07 11:55:22 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

int	run_echo(t_command *command, t_environment *env)
{
	int	arg_count;
	int	i;

	i = 1;
	arg_count = 0;
	while (command->arguments[arg_count])
		arg_count++;
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
