/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:12:52 by smercado          #+#    #+#             */
/*   Updated: 2025/01/08 13:20:24 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	classify_token(char *line, t_token **cur_tok, int *quote_finished,
		int len)
{
	if (!cur_tok)
		exit(1);
	if (((*cur_tok)->type == QUOTE || (*cur_tok)->type == DQUOTE)
		&& !*quote_finished)
		append_q_buf(&line, cur_tok, quote_finished);
	else if (ft_strchr("<>|", *line))
		expand_or_create_operator(*line, cur_tok);
	else if (ft_strchr("\'\"", *line))
		init_quote(*line, cur_tok, len, quote_finished);
	else if (ft_isspace(*line) && (*cur_tok)->type)
		(*cur_tok)->terminated = true;
	else
		append_w_buf(*line, cur_tok, len);
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
	while (ft_isspace(*line))
		line++;
	len = ft_strlen(line);
	while (*line)
	{
		classify_token(line, &cur_tok, &quote_finished, len);
		if (!*line)
			break ;
		line++;
	}
	cur_tok->terminated = true;
	return (tokens);
}
