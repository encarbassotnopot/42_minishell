/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_update.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:36:12 by ecoma-ba          #+#    #+#             */
/*   Updated: 2025/01/07 15:24:25 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "environment_utils.h"

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
			return (env->value);
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
		free_env_entry(prev_env);
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
