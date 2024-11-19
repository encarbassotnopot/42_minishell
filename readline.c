/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smercado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:12:52 by smercado          #+#    #+#             */
/*   Updated: 2024/11/19 13:27:07 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*append_token(t_token *token)
{
	t_token	*my_token;

	my_token = ft_calloc(1, sizeof(t_token));
	if (token)
		token->next = my_token;
	/*my_token->type = 0;*/
	/*my_token->oper = 0;*/
	/*my_token->terminated = 0;*/
	/*my_token->next = 0;*/
	return (my_token);
}

void	append_q_buf(char c, t_token *cur_tok)
{
	if (cur_tok->type == QUOTE && c == '\'')
		return ;
	if (cur_tok->type == DQUOTE && c == '"')
		return ;
	cur_tok->char_buf[ft_strlen(cur_tok->char_buf)] = c;
}

void	expand_or_create_operator(char c, t_token **cur_tok)
{
	(*cur_tok)->terminated = true;
	if ((*cur_tok)->type == OPERATOR)
	{
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
			(*cur_tok)->oper = PIPE;
	}
}

void	append_w_buf(char c, t_token **cur_tok, size_t len)
{
	if ((*cur_tok)->terminated || (*cur_tok)->type != WORD)
	{
		*cur_tok = append_token(*cur_tok);
		(*cur_tok)->char_buf = ft_calloc(len, sizeof(char));
		(*cur_tok)->type = WORD;
	}
	(*cur_tok)->char_buf[ft_strlen((*cur_tok)->char_buf)] = c;
}

void	init_quote(char c, t_token **cur_tok, size_t len)
{
	*cur_tok = append_token(*cur_tok);
	if (c == '\'')
		(*cur_tok)->type = QUOTE;
	else if (c == '"')
		(*cur_tok)->type = DQUOTE;
	(*cur_tok)->char_buf = ft_calloc(len, sizeof(char));
}

t_token	*tokenization(char *line)
{
	int		len;
	t_token	*tokens;
	t_token	*cur_tok;

	tokens = append_token(NULL);
	cur_tok = tokens;
	len = ft_strlen(line);
	while (*line)
	{
		if (!cur_tok)
			exit(1);
		if (cur_tok->type == QUOTE || cur_tok->type == DQUOTE)
			append_q_buf(*line, cur_tok);
		else if (ft_strchr("<>|", *line))
			expand_or_create_operator(*line, &cur_tok);
		else if (ft_strchr("\'\"", *line))
			init_quote(*line, &cur_tok, len);
		else if (ft_isspace(*line))
			cur_tok->terminated = true;
		else
			append_w_buf(*line, &cur_tok, len);
		line++;
	}
	cur_tok->terminated = true;
	return (tokens);
}

void tok_debug(t_token *t)
{
	while (t)
	{
		printf("type: %i\n", t->type);
		printf("chbuf: %s\n", t->char_buf);
		printf("operator: %i\n", t->oper);
		printf("terminated?: %i\n", t->terminated);
		t = t->next;
	}
}

int	main()
{
	char	*line;
	t_token	*tokens;

	while (1)
	{
		line = readline("minishel_test1: ");
		if (*line)
		{
			add_history(line);
			tokens = tokenization(line);
			tok_debug(tokens);
		}
		free(line);
	}
	exit(0);
}


