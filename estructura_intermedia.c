/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   estructura_intermedia.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smercado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:06:14 by smercado          #+#    #+#             */
/*   Updated: 2024/11/27 10:25:13 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_lex	*make_new_lex(t_lex *lex, int *cmd_num)
{
	t_lex	*my_lex;

	my_lex = ft_calloc(1, sizeof(t_lex));
	my_lex->comand = NULL;
	my_lex->comand_num = *cmd_num;
	if (lex)
		lex->next = my_lex;
	return (my_lex);
}

static void	append_redirection_word(t_token *token, t_lex **cur_lex, int *flag)
{
	char	*temp;

	if ((*cur_lex)->comand == NULL)
		(*cur_lex)->comand = ft_strdup(token->char_buf);
	else
	{
		temp = ft_strjoin((*cur_lex)->comand, token->char_buf);
		free((*cur_lex)->comand);
		(*cur_lex)->comand = temp;
	}
	if (!token->terminated)
		*flag = 3;
}

static void	append_first_word(t_token *token, t_lex **cur_lex, int *flag, int *comand_num)
{
	char	*temp;

	if ((cur_lex) && (*cur_lex)->type == REDIRECTION)
		*cur_lex = make_new_lex(*cur_lex, comand_num);
	if ((*cur_lex)->comand == NULL)
	{
		(*cur_lex)->type = PRINCIPAL_WORD;
		(*cur_lex)->comand = ft_strdup(token->char_buf);
	}
	else if (*flag == 2)
	{
		temp = ft_strjoin((*cur_lex)->comand, token->char_buf);
		free((*cur_lex)->comand);
		(*cur_lex)->comand = temp;
	}
	if (!(token->terminated || token->next->type == OPERATOR))
		*flag = 2;
}

static void	append_arguments(t_token *token, t_lex **cur_lex, t_lex **list_lex, int *flag)
{
	t_lex	*tmp;
	t_token	*token_temp;
	int		i;
	char	*str_temp;

	tmp = *list_lex;
	i = 0;
	while (tmp)
	{
		if (tmp->type == PRINCIPAL_WORD && (*cur_lex)->comand_num == tmp->comand_num)
			break ;
		tmp = tmp->next;
	}
	if (!tmp->arguments)
	{
		token_temp = token;
		while (token_temp)
		{
			i++;
			token_temp = token_temp->next;
		}
		tmp->arguments = ft_calloc((i + 1), sizeof(char **));
		tmp->arguments[0] = strdup(token->char_buf);
	}
	else
	{
		while (tmp->arguments[i])
			i++;
		if (*flag == 1)
		{
			str_temp = ft_strjoin(tmp->arguments[i -1], token->char_buf);
			free(tmp->arguments[i -1]);
			tmp->arguments[i - 1] = str_temp;
		}
		else
			tmp->arguments[i] = strdup(token->char_buf);
	}
	if (!token->terminated)
		*flag = 1;
}

static void	manage_words(t_token *token, t_lex **cur_lex, t_lex **list_lex, int *flag, int *comand_num)
{
	t_lex	*tmp_list;

	tmp_list = *list_lex;
	if ((*cur_lex)->type == REDIRECTION && (*flag == 3 || (*flag == 0 && (*cur_lex)->comand == NULL)))
		append_redirection_word(token, cur_lex, flag);
	else if (((*cur_lex)->type == UNSET || ((*cur_lex)->type == PRINCIPAL_WORD && *flag == 2)))
		append_first_word(token, cur_lex, flag, comand_num);
	else if (*flag == 0 && (*cur_lex)->comand && (*cur_lex)->type == REDIRECTION)
	{
		while (tmp_list)
		{
			if (tmp_list->type == PRINCIPAL_WORD && (*cur_lex)->comand_num == tmp_list->comand_num)
				break ;
			tmp_list = tmp_list->next;
		}
		if (tmp_list)
		{
			if (tmp_list->type == PRINCIPAL_WORD && (*cur_lex)->comand_num == tmp_list->comand_num)
				append_arguments(token, cur_lex, list_lex, flag);
		}
		else
			append_first_word(token, cur_lex, flag, comand_num);
	}
	else
		append_arguments(token, cur_lex, list_lex, flag);
}

static void	manage_operators(t_token *token, t_lex **cur_lex, int *comand_num, int *flag)
{
	if ((*cur_lex) && (*cur_lex)->type != UNSET)
		*cur_lex = make_new_lex(*cur_lex, comand_num);
	if (token->oper != PIPE)
	{
		(*cur_lex)->type = REDIRECTION;
		(*cur_lex)->redir_type = token->oper;
	}
	else
	{
		(*cur_lex)->type = PIP;
		(*comand_num)++;
		*flag = 0;
		*cur_lex = make_new_lex(*cur_lex, comand_num);
	}
}

t_lex	*redefine_token_lex(t_token *token)
{
	t_lex	*cur_lex;
	t_lex	*list_lex;
	int		flag;
	int		comand_num;

	comand_num = 1;
	list_lex = make_new_lex(NULL, &comand_num);
	cur_lex = list_lex;
	flag = 0;
	while (token)
	{
		if (token->type == WORD || token->type == DQUOTE || token->type == QUOTE)
			manage_words(token, &cur_lex, &list_lex, &flag, &comand_num);
		else if (token->type == OPERATOR)
			manage_operators(token, &cur_lex, &comand_num, &flag);
		token = token->next;
	}
	return (list_lex);
}
