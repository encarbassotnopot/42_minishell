/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smercado <smercado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:52:37 by ecoma-ba          #+#    #+#             */
/*   Updated: 2025/01/02 13:31:14 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "minishell.h"

int				run_commands(t_command *command, char **envp, t_environment *env);
void			pexit(char *error);
int				my_perror(char *error, int ret);
t_environment	*init_env(char **envp);
void			print_env(t_environment *env);
int				redir_read(char *file);
int				redir_trunc(char *file);
int				redir_append(char *file);
int				overwrite_fd(t_command *cmd, int fd_type, int new_fd);
void			cmd_fd_close(t_command *command);

#endif