/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 11:57:25 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/12/28 14:00:45 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H
# include "minishell.h"

int		here_doc(t_command *command, char *stop);
void	here_clean(t_command *command);
void	here_feed(t_command *command);

#endif