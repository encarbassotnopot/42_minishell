/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:36:12 by ecoma-ba          #+#    #+#             */
/*   Updated: 2025/01/04 15:45:30 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Internal environment functions.
 * Included in environment_utils.h
 */

#include "environment.h"

/**
 * Updates the environment variable `name` with the given value.
 * If no variable with this name is found, nothing else happens.
 */
void	update_env_value(t_environment *env, char *name, char *value)
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
 * Frees the given env entry.
 */
void	free_env_entry(t_environment *env)
{
	free(env->name);
	free(env->value);
	free(env);
}
