/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:52:37 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/12/28 13:34:28 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "minishell.h"

int				run_commands(t_command *command, char **envp);
void			pexit(char *error);
t_environment	*init_env(char **envp);
void			print_env(t_environment *env);
int				redir_read(char *file);
int				redir_trunc(char *file);
int				redir_append(char *file);
int				overwrite_fd(t_command *cmd, int fd_type, int new_fd);
void			cmd_fd_close(t_command *command);

#endif