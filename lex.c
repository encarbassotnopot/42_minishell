/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:12:10 by smercado          #+#    #+#             */
/*   Updated: 2024/12/27 19:06:37 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Adds the word following a redirection as its argument.
 * handle unterminate words (example: if fi"le"1 is found,
	it adds it as "file1").
 */
void	append_redirection_word(t_token *token, t_lex **cur_lex,
		t_token **list_token, t_lex **list_lex)
{
	char	*temp;

	if ((*cur_lex)->command == NULL)
		(*cur_lex)->command = ft_strdup(token->char_buf);
	else
	{
		temp = ft_strjoin((*cur_lex)->command, token->char_buf);
		free((*cur_lex)->command);
		(*cur_lex)->command = temp;
	}
	if (is_terminated(token->next, (*list_token)) && !is_argument(list_lex,
			cur_lex))
		(*cur_lex)->type = REDIRECTION;
	else if (is_terminated(token->next, (*list_token)))
		(*cur_lex)->type = REDIRECTION;
}

/**
 * Sets Principal_Word or concatenates it to the existing command.
 * Creates a new lex if necessary and updates the command number.
 */
void	append_first_word(t_token *tok, t_lex **cur_lex, int *cnum)
{
	char	*temp;

	if (((cur_lex) && (*cur_lex)->type == REDIRECTION)
		|| ((*cur_lex)->type == UNSET && (*cur_lex)->command != NULL
			&& (*cur_lex)->redir_type != OP_UNSET))
		*cur_lex = make_new_lex(*cur_lex, cnum);
	if ((*cur_lex)->command == NULL)
	{
		(*cur_lex)->type = PRINCIPAL_WORD;
		(*cur_lex)->command = ft_strdup(tok->char_buf);
	}
	else
	{
		temp = ft_strjoin((*cur_lex)->command, tok->char_buf);
		free((*cur_lex)->command);
		(*cur_lex)->command = temp;
	}
}
/**
 * Creates a new array of arguments (size of the token list).
 * The first argument is set as the provided token.
 */
void	append_new_argument(t_token *tok, t_lex *tmp)
{
	t_token	*token_temp;
	int		i;

	i = 0;
	token_temp = tok;
	while (token_temp)
	{
		i++;
		token_temp = token_temp->next;
	}
	tmp->arguments = ft_calloc((i + 1), sizeof(char **));
	tmp->arguments[0] = ft_strdup(tok->char_buf);
}
/**
 * Searches for where to attach the argument based on command_num,
 while (argument array++ and adds the token to the last found argument.
 */
void	append_started_argument(t_lex **l_lex, t_lex **cur_lex, t_token *tok)
{
	int		i;
	char	*str_temp;
	t_lex	*tmp;

	tmp = *l_lex;
	while (tmp)
	{
		if ((*cur_lex)->command_num == tmp->command_num
			&& tmp->redir_type == OP_UNSET)
			break ;
		tmp = tmp->next;
	}
	i = 0;
	while (tmp->arguments[i])
		i++;
	str_temp = ft_strjoin(tmp->arguments[i - 1], tok->char_buf);
	free(tmp->arguments[i - 1]);
	tmp->arguments[i - 1] = str_temp;
}
/**
 * Adds a new argument to the end of the list.
 */
void	append_next_argument(t_lex *tmp, t_token *tok)
{
	int	i;

	i = 0;
	while (tmp->arguments[i])
		i++;
	tmp->arguments[i] = ft_strdup(tok->char_buf);
}
