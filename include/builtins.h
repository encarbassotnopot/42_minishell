/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:02:56 by smercado          #+#    #+#             */
/*   Updated: 2025/01/07 11:55:09 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

int	run_cd(t_command *command, t_environment *env);
int	run_echo(t_command *command, t_environment *env);
int	run_pwd(t_command *command, t_environment *env);
int	run_env(t_command *command, t_environment *env);

#endif
