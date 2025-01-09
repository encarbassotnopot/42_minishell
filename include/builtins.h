/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:02:56 by smercado          #+#    #+#             */
/*   Updated: 2025/01/09 13:04:29 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

int	run_cd(t_shell *sh, t_command *command);
int	run_echo(t_shell *sh, t_command *command);
int	run_env(t_shell *sh, t_command *command);
int	run_export(t_shell *sh, t_command *command);
int	run_unset(t_shell *sh, t_command *command);
int	run_pwd(t_shell *sh, t_command *command);
int	run_exit(t_shell *sh, t_command *command);
int	count_args(t_command *command);

#endif
