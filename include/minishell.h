/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:16:26 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/12/28 13:32:55 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "readline/history.h"
# include "readline/readline.h"
# include "structs.h"
# include "system.h"

# define P_READ 0
# define P_WRITE 1

void	init_signals(void);
void	run_signint(int sig);
void	run_sigquit(int sig);

#endif
