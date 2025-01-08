/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 10:31:57 by smercado          #+#    #+#             */
/*   Updated: 2025/01/08 10:04:22 by ecoma-ba         ###   ########.fr       */
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
	char	*pwd;

	pwd = (char *)getcwd(NULL, 0);
	if (!pwd)
		return (printf("minishell : cd: getcwd failed\n"), 1);
	set_env_value(&env, "OLDPWD", pwd);
	free(pwd);
	return (0);
}

/*
 * 1. If directory NULL, set directory to the value of HOME,
 * but if cannot be found- print error.
 */
static int	cd(char *directory, t_environment *env)
{
	int	ret;

	if (!directory)
	{
		update_oldpwd(env);
		directory = (char *)get_const_env_value(env, "HOME");
		if (!directory || directory[0] == '\0')
			return (printf("minishell : cd: HOME not set\n"), 1);
	}
	update_oldpwd(env);
	ret = chdir(directory);
	return (ret);
}

/*
 * 1. if cd has more than 1 arguments, return error.
 * 2. run cd and print ret if is an error type (errno)
 */
int	run_cd(t_shell *sh)
{
	int	ret;
	int	arg_count;

	arg_count = count_args(sh->command);
	if (arg_count > 2)
		return (printf("minishell : cd: too many arguments\n"), 1);
	else
		ret = cd(sh->command->arguments[1], sh->env);
	if (ret == -1)
	{
		printf("minishell: cd: %s: %s\n", strerror(errno),
			sh->command->arguments[1]);
		return (-1);
	}
	return (0);
}
