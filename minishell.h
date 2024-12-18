/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:16:26 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/12/18 12:37:30 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# include "readline/history.h"
# include "readline/readline.h"

typedef enum e_operator_type
{
	OP_UNSET,
	LESS,
	GREAT,
	DLESS,
	DGREAT,
	PIPE,
}						t_operator_type;

typedef struct s_command
{
	char				**arguments;
	t_operator_type		**redir;
	char				**file;
	struct s_command	*next;
}						t_command;

#endif
