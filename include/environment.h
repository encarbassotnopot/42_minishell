/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:03:34 by ecoma-ba          #+#    #+#             */
/*   Updated: 2025/01/02 14:05:03 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H
# include "minishell.h"

t_environment	*init_env(char **envp);
void			print_env(t_environment *env);
char			*get_env_value(t_environment *env, char *name);
void			set_env_value(t_environment **env, char *name, char *value);
void			unset_env_value(t_environment **env, char *name);
#endif