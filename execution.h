/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:52:37 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/12/26 11:41:52 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "minishell.h"

typedef struct s_environment
{
	char					*name;
	char					*value;
	struct s_environment	*next;
}							t_environment;

int							run_commands(t_command *command, char **envp);
void						pexit(char *error);
t_environment				*init_env(char **envp);
void						print_env(t_environment *env);

#endif