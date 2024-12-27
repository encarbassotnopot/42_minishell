/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:16:26 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/12/19 16:20:04 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>
# include "readline/history.h"
# include "readline/readline.h"

# define P_READ 0
# define P_WRITE 1

typedef enum e_operator_type
{
	OP_UNSET,
	LESS,   // <
	GREAT,  // >
	DLESS,  // <<
	DGREAT, // >>
	PIPE,   // |
}						t_operator_type;

typedef struct s_command
{
	char				**arguments;
	t_operator_type		*redir;
	char				**file;
	int					fds[2];
	struct s_command	*next;
}						t_command;

void					init_signals(void);
void					run_signint(int sig);
void					run_sigquit(int sig);

#endif
