/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:23:16 by ecoma-ba          #+#    #+#             */
/*   Updated: 2025/01/04 15:42:54 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "environment_utils.h"

/**
 * Initializes the env list with the envp given by main.
 */
t_environment	*init_env(char **envp)
{
	int				i;
	t_environment	base;
	t_environment	*current;

	i = -1;
	if (!envp)
		return (NULL);
	base.next = NULL;
	current = &base;
	while (envp[++i])
	{
		current->next = ft_calloc(1, sizeof(t_environment));
		if (!current->next)
			break ;
		current = current->next;
		current->name = ft_substr(envp[i], 0, ft_strchr_idx(envp[i], '='));
		current->value = ft_strdup(ft_strchr(envp[i], '=') + 1);
	}
	return (base.next);
}

/**
 * Generates a char** with all the environment variables.
 */
char	**gen_env(t_environment *env)
{
	char			**envp;
	t_environment	*my_env;
	size_t			i;

	my_env = env;
	i = 0;
	while (my_env)
	{
		my_env = my_env->next;
		i++;
	}
	envp = ft_calloc(i + 1, sizeof(char *));
	my_env = env;
	i = 0;
	while (my_env && envp)
	{
		envp[i] = ft_strjoins(3, my_env->name, "=", my_env->value);
		my_env = my_env->next;
		i++;
	}
	return (envp);
}

void	free_env(t_environment **env)
{
	t_environment	*my_env;
	t_environment	*last_env;

	if (!env)
		return ;
	my_env = *env;
	while (my_env)
	{
		last_env = my_env;
		my_env = my_env->next;
		free_env_entry(last_env);
	}
	*env = NULL;
}
