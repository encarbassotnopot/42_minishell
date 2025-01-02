/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smercado <smercado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 10:31:57 by smercado          #+#    #+#             */
/*   Updated: 2025/01/02 14:02:05 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void    set_env_value(t_environment *env, char *name, char *value)
{
    while (env)
    {
        if (ft_strcmp(env->name, name) == 0)
        {
            free(env->value);
            env->value = ft_strdup(value);
            return ;
        }
        env = env->next;
    }
}

int change_to_oldpwd(t_environment *env)
{
    int     ret;
    char    *path_envp;
    
    path_envp = get_env_value(env, "OLDPWD");
        if (!path_envp)
            return (printf("minishell : cd: OLDPWD not set\n"), -1);
    update_oldpwd(env);
    ret = chdir(path_envp);
    return (ret);
}

int update_oldpwd(t_environment *env)
{
    char    *oldpwd;
    char  	*pwd;

	pwd = getcwd(NULL, 0);
    if (!pwd)
        return (printf("minishell : cd: getcwd failed\n"), 1);
    if (!(oldpwd = get_env_value(env, "OLDPWD")))
        return (printf("minishell : cd: OLDPWD not set\n"), 1);
    set_env_value(env, "OLDPWD", pwd);
    return (0);
}

/*
 * 1. If directory NULL, set directory to the value of HOME, but if cannot be found- print error.
    * 2. If directory is "-", go to the previous directory.
    * 3 If directory is not "-", update the OLDPWD and change the directory to the new directory.
*/
int cd(char *directory, t_environment *env)
{
    int ret;

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

int run_cd(t_command *command, t_environment *env)
{
    int ret;
    
    if (command->arguments[2])
        return (printf("minishell : cd: too many arguments\n"), 1);
	else
		ret = cd(command->arguments[1], env);
	printf("ret is %d\n", ret);
    return (0);
}
