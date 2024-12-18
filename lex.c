/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:12:10 by smercado          #+#    #+#             */
/*   Updated: 2024/12/18 10:23:08 by smercado         ###   ########.fr       */
/*   Updated: 2024/12/18 09:46:21 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_lex	*make_new_lex(t_lex *lex, int *cmd_num)
{
	t_lex	*my_lex;

	my_lex = ft_calloc(1, sizeof(t_lex));
	my_lex->command = NULL;
	my_lex->command_num = *cmd_num;
	if (lex)
		lex->next = my_lex;
	return (my_lex);
}

void	append_redirection_word(t_token *token, t_lex **cur_lex, t_token **list_token, t_lex **list_lex)
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
	if (is_terminated(token->next, (*list_token)) && !is_argument(list_lex, cur_lex))
		(*cur_lex)->type = UNSET;
	else if (is_terminated(token->next, (*list_token)))
		(*cur_lex)->type = PRINCIPAL_WORD;
}

void	append_first_word(t_token *tok, t_lex **cur_lex, int *cnum)
{
	char	*temp;

	if (((cur_lex) && (*cur_lex)->type == REDIRECTION) || ((*cur_lex)->type == UNSET && \
		(*cur_lex)->command != NULL && (*cur_lex)->redir_type != OP_UNSET))
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

void	append_started_argument(t_lex **l_lex, t_lex **cur_lex, t_token *tok)
{
	int		i;
	char	*str_temp;
	t_lex	*tmp;

	tmp = *l_lex;
	while (tmp)
	{
		if ((*cur_lex)->command_num == tmp->command_num && tmp->redir_type == OP_UNSET)
			break ;
		tmp = tmp->next;
	}
	i = 0;
	while(tmp->arguments[i])
		i++;
	str_temp = ft_strjoin(tmp->arguments[i -1], tok->char_buf);
	free(tmp->arguments[i - 1]);
	tmp->arguments[i - 1] = str_temp;
}

void	append_next_argument(t_lex *tmp, t_token *tok)
{
	int		i;

	i = 0;
	while (tmp->arguments[i])
		i++;
	tmp->arguments[i] = ft_strdup(tok->char_buf);
}
