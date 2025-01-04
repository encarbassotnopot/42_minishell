/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:52:37 by ecoma-ba          #+#    #+#             */
/*   Updated: 2025/01/04 13:51:56 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "minishell.h"

int		run_commands(t_command *command, t_environment *env, t_shell *shinfo);
void	pexit(char *error);
int		my_perror(char *error, int ret);
int		redir_read(char *file);
int		redir_trunc(char *file);
int		redir_append(char *file);
int		overwrite_fd(t_command *cmd, int fd_type, int new_fd);
void	cmd_fd_close(t_command *command);

#endif