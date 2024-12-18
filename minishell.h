/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:16:26 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/12/18 10:23:44 by smercado         ###   ########.fr       */
/*   Created: 2024/11/14 10:19:09 by smercado          #+#    #+#             */
/*   Updated: 2024/12/18 10:12:13 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "readline/history.h"
# include "readline/readline.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

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
	char				*word;
	char				**arguments;
	t_operator_type		**redir;
	char				**file;
	struct s_command	*next;
}						t_command;

t_token *tokenization(char *line);
void	expand_tokens(t_token *const token);
void	print_operator(t_operator_type e);

// lex operations
t_lex	*redefine_token_lex(t_token *token);
void	manage_operators(t_token *token, t_lex **cur_lex, int *command_num);
void	manage_words(t_token *token, t_lex **cur_lex, t_lex **list_lex, int *command_num);
int		is_argument(t_lex **list_lex, t_lex **cur_lex);
int		is_terminated(t_token *token, t_token *list_tok);
t_lex	*make_new_lex(t_lex *lex, int *cmd_num);
void	lex_debug(t_lex *lex);
void	append_redirection_word(t_token *token, t_lex **cur_lex, t_token **list_token, t_lex **list_lex);
void	append_first_word(t_token *tok, t_lex **cur_lex, int *cnum);
void	append_started_argument(t_lex **l_lex, t_lex **cur_lex, t_token *tok);
void	append_next_argument(t_lex *tmp, t_token *tok);
void	append_args(t_token *tok, t_lex **cur_lex, t_lex **l_lex);
void	append_new_argument(t_token *tok, t_lex *tmp);

// comandes
t_command	*redefine_lex(t_lex *list_lex);
void		command_debug(t_command *command);

// comandes_utils
void	parse_error(t_command **command, t_lex **list_lex, char *str);
void free_lex_list(t_lex **list_lex);
void free_command_list(t_command **command);
void free_lex_node(t_lex *node);
void free_command_node(t_command *node);
void	free_cmd_node(t_command *cmd);
void	free_comandes(t_command *command);

#endif
