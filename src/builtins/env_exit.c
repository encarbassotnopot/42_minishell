/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:37:26 by ecoma-ba          #+#    #+#             */
/*   Updated: 2025/01/08 10:03:59 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

/**
 * Prints the whole environment.
 */
int	run_env(t_shell *sh)
{
	t_environment	*env;

	env = sh->env;
	while (env)
	{
		printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return (0);
}

/**
 * Exits the shell (or the child process).
 */
int	run_exit(t_shell *sh)
{
	cleanup(sh, NULL, 0);
	return (0);
}
