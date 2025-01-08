/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:16:26 by ecoma-ba          #+#    #+#             */
/*   Updated: 2025/01/08 12:59:54 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "structs.h"
# include "system.h"
# include "builtins.h"
# include "libft.h"
# include "readline/history.h"
# include "readline/readline.h"

# define P_READ 0
# define P_WRITE 1

void	cleanup(t_shell *shinfo, char *msg, int status);
void	interactive_signals(void);
void	non_interactive_signals(void);
void	here_signals(void);
void	free_strarr(char **str);

#endif
