/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:02:56 by smercado          #+#    #+#             */
/*   Updated: 2025/01/02 14:14:39 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

int	change_to_oldpwd(t_environment *env);
int	update_oldpwd(t_environment *env);
int	cd(char *directory, t_environment *env);
int	run_cd(t_command *command, t_environment *env);

#endif
