/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:43:34 by smercado          #+#    #+#             */
/*   Updated: 2025/01/09 13:06:43 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "environment.h"

int	run_unset(t_shell *sh, t_command *command)
{
	int	arg_count;
	int	i;

	i = 1;
	arg_count = count_args(command);
	if (arg_count <= 1)
		return (0);
	while (arg_count > i)
	{
		unset_env_value(&sh->env, command->arguments[i]);
		i++;
	}
	return (0);
}

int	run_echo(t_shell *sh, t_command *command)
{
	int		arg_count;
	int		i;
	bool	flag;

	(void)sh;
	flag = false;
	i = 0;
	arg_count = count_args(command);
	if (arg_count == 1)
		printf("\n");
	while (ft_strcmp(command->arguments[++i], "-n") == 0)
		flag = true;
	while (arg_count - 1 > i)
	{
		printf("%s ", command->arguments[i]);
		i++;
	}
	printf("%s", command->arguments[i]);
	if (!flag)
		printf("\n");
	return (0);
}
