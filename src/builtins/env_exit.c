/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:37:26 by ecoma-ba          #+#    #+#             */
/*   Updated: 2025/01/07 15:03:22 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

/**
 * Prints the whole environment.
 */
int	run_env(t_command *command, t_environment *env, t_shell *shinfo)
{
	(void)command;
	(void)shinfo;
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
void	run_exit(t_command *command, t_environment *env, t_shell *shinfo)
{
	(void)command;
	(void)env;
	cleanup(shinfo, NULL, 0);
}
