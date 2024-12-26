/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:23:16 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/12/26 12:00:09 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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

void	print_env(t_environment *env)
{
	while (env)
	{
		printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}