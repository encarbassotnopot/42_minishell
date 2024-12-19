/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:19:09 by smercado          #+#    #+#             */
/*   Updated: 2024/12/19 14:25:36 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "minishell.h"

typedef enum e_token_type
{
	TYPE_UNSET,
	WORD,
	OPERATOR,
	QUOTE,
	DQUOTE,
}					t_token_type;

typedef enum e_lex_type
{
	UNSET,
	PRINCIPAL_WORD,
	PIP,
	REDIRECTION,
	ASSIGNMENT,
}					t_lex_type;

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
	char			*command;
	int				command_num;
	char			**arguments;
	t_operator_type	redir_type;
	struct s_lex	*next;
}					t_lex;

t_token				*tokenization(char *line);
void				expand_tokens(t_token *const token);
void				print_operator(t_operator_type e);

// lex operations
t_lex				*redefine_token_lex(t_token *token);
void				manage_operators(t_token *token, t_lex **cur_lex,
						int *command_num);
void				manage_words(t_token *token, t_lex **cur_lex,
						t_lex **list_lex, int *command_num);
int					is_argument(t_lex **list_lex, t_lex **cur_lex);
int					is_terminated(t_token *token, t_token *list_tok);
int					is_word(t_token *token);
t_lex				*make_new_lex(t_lex *lex, int *cmd_num);
void				lex_debug(t_lex *lex);
void				append_redirection_word(t_token *token, t_lex **cur_lex,
						t_token **list_token, t_lex **list_lex);
void				append_first_word(t_token *tok, t_lex **cur_lex, int *cnum);
void				append_started_argument(t_lex **l_lex, t_lex **cur_lex,
						t_token *tok);
void				append_next_argument(t_lex *tmp, t_token *tok);
void				append_args(t_token *tok, t_lex **cur_lex, t_lex **l_lex);
void				append_new_argument(t_token *tok, t_lex *tmp);

// comandes
t_command			*redefine_lex(t_lex *list_lex);
void				command_debug(t_command *command);

// comandes_utils
void				parse_error(t_command **command, t_lex **list_lex,
						char *str);
void				free_lex_list(t_lex *list_lex);
void				free_lex_node(t_lex *node);
void				free_cmd_node(t_command *cmd);
void				free_comandes(t_command *command);
void				free_tokens(t_token *tokens);

#endif
