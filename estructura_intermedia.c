/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   estructura_intermedia.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smercado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:06:14 by smercado          #+#    #+#             */
/*   Updated: 2024/11/26 15:54:03 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_lex	*make_new_lex(t_lex *lex, int *cmd_num)
{
	t_lex *my_lex;
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
	if (token->terminated)
		*flag = 2;
}

static void	append_or_create_first_word(t_token *token, t_lex **cur_lex, int *flag, int *comand_num)
{
	char	*temp;

	if ((cur_lex) && (*cur_lex)->type == REDIRECTION)
		*cur_lex = make_new_lex(*cur_lex, comand_num);
	if ((*cur_lex)->comand == NULL)
	{
		(*cur_lex)->type = PRINCIPAL_WORD;
		(*cur_lex)->comand = ft_strdup(token->char_buf);
	}
	else
	{
		temp = ft_strjoin((*cur_lex)->comand, token->char_buf);
		 free((*cur_lex)->comand);
           	 (*cur_lex)->comand = temp;
	}
	if ((token->terminated || token->next->type == OPERATOR))
		*flag = 1;
}

static void append_arguments(t_token *token, t_lex **cur_lex, t_lex **list_lex)
{
	t_lex	*tmp;
	t_token	*token_temp;
	int		i;

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
				tmp->arguments[i] = strdup(token->char_buf);
			}
}

static void	manage_words(t_token *token, t_lex **cur_lex, t_lex **list_lex, int *flag, int *comand_num)
{
	if ((*cur_lex)->type == REDIRECTION && *flag != 2)
		append_redirection_word(token, cur_lex, flag);
	else if (((*cur_lex)->type == UNSET || (*cur_lex)->type == PRINCIPAL_WORD) && *flag != 1)
	        append_or_create_first_word(token, cur_lex, flag, comand_num);
	else
		append_arguments(token, cur_lex, list_lex);
}

static void	manage_operators(t_token *token, t_lex **cur_lex, int *comand_num, int *flag)
{
	if (*cur_lex)
		*cur_lex = make_new_lex(*cur_lex, comand_num);
	if (token->oper != PIPE)
		(*cur_lex)->type = REDIRECTION;
	else
	{
		//if (*cur_lex)
		//	*cur_lex = make_new_lex(*cur_lex, comand_num);
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
