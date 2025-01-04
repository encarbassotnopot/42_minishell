/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:23:16 by ecoma-ba          #+#    #+#             */
/*   Updated: 2025/01/04 12:39:11 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

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
 * Prints the whole environment.
 */
void	print_env(t_environment *env)
{
	while (env)
	{
		printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
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

/**
 * Searches for a environment variable named `name` and
 * returns a pointer to its value.
 * The pointer is NULL if the variable is unset.
 */
const char	*get_const_env_value(t_environment *env, char *name)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

/**
 * Searches for a environment variable named `name` and
 * returns a copy of its value.
 * The pointer is NULL if the variable is unset.
 */
char	*get_env_value(t_environment *env, char *name)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

/**
 * Updates the environment variable `name` with the given value.
 * If no variable with this name is found, nothing else happens.
 */
static void	update_env_value(t_environment *env, char *name, char *value)
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

/**
 * Creates or updates the environment variable `name` with the given value.
 * If one of the parameters is NULL it does nothing.
 */
void	set_env_value(t_environment **env, char *name, char *value)
{
	t_environment	*new_env;

	if (!env || !name || !value)
		return ;
	if (get_const_env_value(*env, name))
	{
		update_env_value(*env, name, value);
		return ;
	}
	new_env = ft_calloc(1, sizeof(t_environment));
	if (!new_env)
		return ;
	new_env->name = ft_strdup(name);
	new_env->value = ft_strdup(value);
	new_env->next = *env;
	*env = new_env;
}

/**
 * Frees the given env entry.
 */
static void	free_env_entry(t_environment *env)
{
	free(env->name);
	free(env->value);
	free(env);
}

/**
 * Deletes a environment variable.
 */
void	unset_env_value(t_environment **env, char *name)
{
	t_environment	*prev_env;
	t_environment	*next_env;

	if (!env || !name)
		return ;
	prev_env = *env;
	if (ft_strcmp(prev_env->name, name) == 0)
	{
		next_env = prev_env->next;
		free_env_entry(prev_env->next);
		*env = next_env;
		return ;
	}
	while (prev_env->next)
	{
		if (ft_strcmp(prev_env->next->name, name) == 0)
		{
			next_env = prev_env->next->next;
			free_env_entry(prev_env->next);
			prev_env->next = next_env;
		}
		prev_env = prev_env->next;
	}
}

void	free_env(t_environment **env)
{
	t_environment *my_env;
	t_environment *last_env;

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