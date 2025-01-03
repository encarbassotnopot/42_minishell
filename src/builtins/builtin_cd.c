/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smercado <smercado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 10:31:57 by smercado          #+#    #+#             */
/*   Updated: 2025/01/03 18:07:31 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "environment.h"
#include "minishell.h"

/*
 * 1. get actual pwd and put it in oldpwd (if no exist, created)
 */
static int	update_oldpwd(t_environment *env)
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
 * 1. get oldpwd (if no exist ->print error), updated old path with actual path
 * 2. put oldpwd as actual.
 */
static int	change_to_oldpwd(t_environment *env)
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

/*
 * 1. If directory NULL, set directory to the value of HOME,
 * but if cannot be found- print error.
 * 2. If directory is "-", go to the previous directory.
 * 3 If directory is not "-",
 * update the OLDPWD and change the directory to the new directory.
 */
static int	cd(char *directory, t_environment *env)
{
	int	ret;

	if (!directory)
	{
		update_oldpwd(env);
		directory = get_env_value(env, "HOME");
		if (!directory || directory[0] == '\0')
			return (printf("minishell : cd: HOME not set\n"), 1);
	}
	if (ft_strcmp(directory, '-') == 0)
		ret = change_to_oldpwd(env);
	else if (ft_strcmp(directory, '.') == 0)
		return (0);
	else if (ft_strcmp(directory, '..') == 0)
		printf("aqui .., de moment res xD\n");
	else
	{
		update_oldpwd(env);
		ret = chdir(directory);
	}
	return (ret);
}

/*
 * 1. if cd has more than 1 arguments, return error.
 * 2. run cd and print ret if is an error type (errno)
 */
int	run_cd(t_command *command, t_environment *env)
{
	int	ret;
	int	arg_count;

	arg_count = 0;
	while (command->arguments[arg_count])
		arg_count++;
	if (arg_count > 2)
		return (printf("minishell : cd: too many arguments\n"), 1);
	else
		ret = cd(command->arguments[1], env);
	if (ret == -1)
	{
		printf("minishell: cd: %s: %s\n", strerror(errno),
			command->arguments[1]);
		return (-1);
	}
	return (0);
}
