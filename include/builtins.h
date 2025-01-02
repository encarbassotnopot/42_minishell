/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smercado <smercado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:02:56 by smercado          #+#    #+#             */
/*   Updated: 2025/01/02 13:33:39 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
#include "minishell.h"

void	set_env_value(t_environment *env, char *name, char *value);
int		change_to_oldpwd(t_environment *env);
int		update_oldpwd(t_environment *env);
int		cd(char *directory, t_environment *env);
int		run_cd(t_command *command, t_environment *env);
char	*get_env_value(t_environment *env, char *name);

#endif
