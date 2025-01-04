/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:16:26 by ecoma-ba          #+#    #+#             */
/*   Updated: 2025/01/04 15:59:36 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "system.h"
# include "readline/history.h"
# include "readline/readline.h"
# include "structs.h"
# include "builtins.h"

# define P_READ 0
# define P_WRITE 1

void	cleanup(t_shell *shinfo, char *msg, int status);
void	init_signals(void);
void	run_signint(int sig);
void	run_sigquit(int sig);
void	free_strarr(char **str);

#endif
