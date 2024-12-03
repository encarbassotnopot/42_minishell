/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smercado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:19:09 by smercado          #+#    #+#             */
/*   Updated: 2024/12/03 12:05:34 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include "libft.h"
# include "readline/history.h"
# include "readline/readline.h"

typedef enum e_token_type
{
	TYPE_UNSET,
	WORD,
	OPERATOR,
	QUOTE,
	DQUOTE,
}					t_token_type;

typedef enum e_operator_type
{
	OP_UNSET,
	LESS,
	GREAT,
	DLESS,
	DGREAT,
	PIPE,
}					t_operator_type;

/**
 *
 */
typedef struct s_token
{
	char			*char_buf;
	t_token_type	type;
	t_operator_type	oper;
	bool			terminated;
	struct s_token	*next;
}					t_token;

t_token *tokenization(char *line);
void	expand_tokens(t_token *const token);
#endif
