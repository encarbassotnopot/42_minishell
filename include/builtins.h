/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:02:56 by smercado          #+#    #+#             */
/*   Updated: 2025/01/07 13:20:41 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"
int	run_cd(t_command *command, t_environment *env, t_shell *shinfo);
int	run_echo(t_command *command, t_environment *env, t_shell *shinfo);
int	run_env(t_command *command, t_environment *env, t_shell *shinfo);
int	run_export(t_command *command, t_environment *env, t_shell *shinfo);
int	run_pwd(t_command *command, t_environment *env, t_shell *shinfo);
int	count_args(t_command *command);

#endif
