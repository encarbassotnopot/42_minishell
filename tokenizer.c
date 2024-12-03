/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smercado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:12:52 by smercado          #+#    #+#             */
/*   Updated: 2024/12/03 13:36:52 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*append_token(t_token *token)
{
	t_token	*my_token;

	my_token = ft_calloc(1, sizeof(t_token));
	if (token)
	{
		if (token->type == TYPE_UNSET)
			return token;
		token->next = my_token;
	}
	return (my_token);
}

void	append_q_buf(char **c, t_token **cur_tok, int *quote_finished)
{
	while (**c)
	{
		if ((*cur_tok)->type == QUOTE && **c == '\'')
		{
			(*c)++;
			*quote_finished = 1;
			break ;
		}
		else if ((*cur_tok)->type == DQUOTE && **c == '"')
		{
			(*c)++;
			*quote_finished = 1;
			break ;
		}
		else
			(*cur_tok)->char_buf[ft_strlen((*cur_tok)->char_buf)] = **c;
		(*c)++;
	}
}

void	expand_or_create_operator(char c, t_token **cur_tok)
{
	if ((*cur_tok)->type == OPERATOR && !(*cur_tok)->terminated)
	{
		(*cur_tok)->terminated = true;
		if ((*cur_tok)->oper == LESS && c == '<')
			(*cur_tok)->oper = DLESS;
		else if ((*cur_tok)->oper == GREAT && c == '>')
			(*cur_tok)->oper = DGREAT;
	}
	else
	{
		*cur_tok = append_token(*cur_tok);
		(*cur_tok)->type = OPERATOR;
		if (c == '<')
			(*cur_tok)->oper = LESS;
		else if (c == '>')
			(*cur_tok)->oper = GREAT;
		else if (c == '|')
		{
			(*cur_tok)->oper = PIPE;
			(*cur_tok)->terminated = true;
		}
	}
}

void	append_w_buf(char c, t_token **cur_tok, size_t len)
{
	if ((*cur_tok)->terminated || (*cur_tok)->type != WORD)
	{
		*cur_tok = append_token(*cur_tok);
		(*cur_tok)->char_buf = ft_calloc(len + 1, sizeof(char));
		(*cur_tok)->type = WORD;
	}
	(*cur_tok)->char_buf[ft_strlen((*cur_tok)->char_buf)] = c;
}

void	init_quote(char c, t_token **cur_tok, size_t len, int *quote_finished)
{
	*cur_tok = append_token(*cur_tok);
	*quote_finished = 0;
	if (c == '\'')
		(*cur_tok)->type = QUOTE;
	else if (c == '"')
		(*cur_tok)->type = DQUOTE;
	(*cur_tok)->char_buf = ft_calloc(len + 1, sizeof(char));
}

t_token	*tokenization(char *line)
{
	int		len;
	int		quote_finished;
	t_token	*tokens;
	t_token	*cur_tok;

	tokens = append_token(NULL);
	cur_tok = tokens;
	quote_finished = 0;
	len = ft_strlen(line);
	while (*line)
	{
		if (!cur_tok)
			exit(1);
		if ((cur_tok->type == QUOTE || cur_tok->type == DQUOTE) && !quote_finished)
			append_q_buf(&line, &cur_tok, &quote_finished);
		else if (ft_strchr("<>|", *line))
			expand_or_create_operator(*line, &cur_tok);
		else if (ft_strchr("\'\"", *line))
			init_quote(*line, &cur_tok, len, &quote_finished);
		else if (ft_isspace(*line) && cur_tok->type)
			cur_tok->terminated = true;
		else
			append_w_buf(*line, &cur_tok, len);
		if (!*line)
			break ;
		line++;
	}
	cur_tok->terminated = true;
	return (tokens);
}
