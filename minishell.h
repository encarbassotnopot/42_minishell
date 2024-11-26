/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smercado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:19:09 by smercado          #+#    #+#             */
/*   Updated: 2024/11/26 10:57:16 by smercado         ###   ########.fr       */
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
typedef enum e_lex_type
{
	UNSET,
	PRINCIPAL_WORD,
	PIP,
	REDIRECTION,
}		t_lex_type;

typedef struct s_token
{
	char			*char_buf;
	t_token_type	type;
	t_operator_type	oper;
	bool			terminated;
	struct s_token	*next;
}					t_token;

typedef struct s_lex
{
	t_lex_type		type;
	char			*comand;
	int				comand_num;
	char			**arguments;
	t_operator_type	redir_type;
	struct s_lex	*next;
}					t_lex;

t_token *tokenization(char *line);
t_lex	*redefine_token_lex(t_token *token);
void	lex_debug(t_lex *lex);

#endif
