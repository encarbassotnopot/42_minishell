/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 10:31:57 by smercado          #+#    #+#             */
/*   Updated: 2025/01/03 15:04:59 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "builtins.h"
#include "environment.h"
#include "minishell.h"

int	change_to_oldpwd(t_environment *env)
{
	int		ret;
	char	*path_envp;

	path_envp = get_env_value(env, "OLDPWD");
	if (!path_envp)
		return (printf("minishell : cd: OLDPWD not set\n"), -1);
	update_oldpwd(env);
	ret = chdir(path_envp);
	return (ret);
}

int	update_oldpwd(t_environment *env)
{
	char	*oldpwd;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (printf("minishell : cd: getcwd failed\n"), 1);
	if (!(oldpwd = get_env_value(env, "OLDPWD")))
		return (printf("minishell : cd: OLDPWD not set\n"), 1);
	set_env_value(&env, "OLDPWD", pwd);
	return (0);
}

/*
 * 1. If directory NULL, set directory to the value of HOME,
 * but if cannot be found- print error.
 * 2. If directory is "-", go to the previous directory.
 * 3 If directory is not "-",
 * update the OLDPWD and change the directory to the new directory.
 */
int	cd(char *directory, t_environment *env)
{
	int	ret;

	if (!directory)
	{
		update_oldpwd(env);
		directory = get_env_value(env, "HOME");
		if (!directory || directory[0] == '\0')
			return (printf("minishell : cd: HOME not set\n"), 1);
	}
	if (directory[0] == '-')
		ret = change_to_oldpwd(env);
	else
	{
		update_oldpwd(env);
		ret = chdir(directory);
	}
	return (ret);
}

int	run_cd(t_command *command, t_environment *env)
{
	int		ret;
	int		arg_count;
	char	*join_args;

	arg_count = 0;
	while (command->arguments[arg_count])
		arg_count++;
	if (arg_count > 2)
		return (printf("minishell : cd: too many arguments\n"), 1);
	else
		ret = cd(command->arguments[1], env);
	if (ret == -1)
	{
		printf("minishell: cd: %s: %s\n", strerror(errno), command->arguments[1]);
		return (-1);
	}
	return (0);
}
