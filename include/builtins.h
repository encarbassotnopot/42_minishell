/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smercado <smercado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:02:56 by smercado          #+#    #+#             */
/*   Updated: 2025/01/07 13:13:57 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

int		run_cd(t_command *command, t_environment *env, t_shell *shinfo);
int		run_echo(t_command *command, t_shell *shinfo);
int		run_pwd(t_command *command, t_environment *env, t_shell *shinfo);
void	print_env(t_environment *env);
int		count_args(t_command *command);

#endif
