/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smercado <smercado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:16:26 by ecoma-ba          #+#    #+#             */
/*   Updated: 2025/01/08 10:46:38 by smercado         ###   ########.fr       */
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

void		cleanup(t_shell *shinfo, char *msg, int status);
void		init_signals(void);
void		here_signals(void);
void		free_strarr(char **str);

#endif
