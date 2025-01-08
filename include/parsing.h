/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:19:09 by smercado          #+#    #+#             */
/*   Updated: 2025/01/08 13:13:42 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "minishell.h"

t_token			*tokenization(char *line);
void			expand_tokens(t_token *const token, t_environment *env,
					t_shell *shinfo);
void			print_operator(t_operator_type e);

// tok_utils

t_token			*append_token(t_token *token);
void			append_q_buf(char **c, t_token **cur_tok, int *quote_finished);
void			expand_or_create_operator(char c, t_token **cur_tok);
void			append_w_buf(char c, t_token **cur_tok, size_t len);
void			init_quote(char c, t_token **cur_tok, size_t len,
					int *quote_finished);

// lex operations
t_lex			*redefine_token_lex(t_token *token);
void			manage_operators(t_token *token, t_lex **cur_lex,
					int *command_num);
void			manage_words(t_token *token, t_lex **cur_lex, t_lex **list_lex,
					int *command_num);
int				is_argument(t_lex **list_lex, t_lex **cur_lex);
int				is_terminated(t_token *token, t_token *list_tok);
int				is_word(t_token *token);
t_lex			*make_new_lex(t_lex *lex, int *cmd_num);
void			lex_debug(t_lex *lex);
void			append_redirection_word(t_token *token, t_lex **cur_lex,
					t_token **list_token, t_lex **list_lex);
void			append_first_word(t_token *tok, t_lex **cur_lex, int *cnum);
void			append_started_argument(t_lex **l_lex, t_lex **cur_lex,
					t_token *tok);
void			append_next_argument(t_lex *tmp, t_token *tok);
void			append_args(t_token *tok, t_lex **cur_lex, t_lex **l_lex);
void			append_new_argument(t_token *tok, t_lex *tmp);

// expansions_utils
size_t			get_var_len(char *str);
char			*get_next_var(char *str);
unsigned int	var_count(char *str);

// comandes
t_command		*redefine_lex(t_lex *list_lex);
void			command_debug(t_command *command);

// comandes_utils
void			free_lex_list(t_lex **list_lex);
void			free_lex_node(t_lex **node);
void			free_comanda(t_command **cmd);
void			free_comandes(t_command **command);
void			free_tokens(t_token **tokens);
int				checker_lex(t_lex *lex);

void			here_clean(t_command *command);

#endif
