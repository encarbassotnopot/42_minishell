/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:42:14 by ecoma-ba          #+#    #+#             */
/*   Updated: 2025/01/04 15:42:45 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_UTILS_H
# define ENVIRONMENT_UTILS_H
# include "minishell.h"

void	update_env_value(t_environment *env, char *name, char *value);
void	free_env_entry(t_environment *env);
#endif