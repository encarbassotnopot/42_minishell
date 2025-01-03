/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:25:49 by ecoma-ba          #+#    #+#             */
/*   Updated: 2025/01/03 16:36:45 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "system.h"

typedef enum e_token_type
{
	TYPE_UNSET,
	WORD,
	OPERATOR,
	QUOTE,
	DQUOTE,
}							t_token_type;

typedef enum e_operator_type
{
	OP_UNSET,
	LESS,
	GREAT,
	DLESS,
	DGREAT,
	PIPE,
}							t_operator_type;

typedef enum e_lex_type
{
	UNSET,
	PRINCIPAL_WORD,
	PIP,
	REDIRECTION,
	ASSIGNMENT,
}							t_lex_type;

typedef struct s_environment
{
	char					*name;
	char					*value;
	struct s_environment	*next;
}							t_environment;

typedef struct s_here_buf
{
	char					*line;
	struct s_here_buf		*next;
}							t_here_buf;

typedef struct s_token
{
	char					*char_buf;
	t_token_type			type;
	t_operator_type			oper;
	bool					terminated;
	struct s_token			*next;
}							t_token;

typedef struct s_lex
{
	t_lex_type				type;
	char					*command;
	int						command_num;
	char					**arguments;
	t_operator_type			redir_type;
	struct s_lex			*next;
}							t_lex;

typedef struct s_command
{
	char					**arguments;
	t_operator_type			*redir;
	char					**file;
	int						fds[2];
	t_here_buf				*here_buf;
	struct s_command		*next;
	pid_t					pid;
}							t_command;

typedef struct s_shell
{
	int						exit;
	t_command				*command;
	t_environment			*env;
}							t_shell;

#endif