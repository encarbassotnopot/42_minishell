/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smercado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:12:52 by smercado          #+#    #+#             */
/*   Updated: 2024/11/19 15:14:26 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_operator(t_operator_type e)
{
	if (e == OP_UNSET)
		printf("type: OP_UNSET\n");
	if (e == LESS)
		printf("type: LESS <\n");
	if (e == GREAT)
		printf("type: GREAT >\n");
	if (e == DLESS)
		printf("type: DLESS <<\n");
	if (e == DGREAT)
		printf("type: DGREAT >>\n");
	if (e == PIPE)
		printf("type: PIPE |\n");

}

void	print_type(t_token_type e)
{
	if (e == TYPE_UNSET)
		printf("type: TYPE_UNSET\n");
	if (e == WORD)
		printf("type: WORD\n");
	if (e == OPERATOR)
		printf("type: OPERATOR\n");
	if (e == QUOTE)
		printf("type: QUOTE\n");
	if (e == DQUOTE)
		printf("type: DQUOTE\n");
}

void	tok_debug(t_token *t)
{
	while (t)
	{
		print_type(t->type);
		printf("chbuf: %s\n", t->char_buf);
		print_operator(t->oper);
		printf("terminated?: %i\n\n", t->terminated);
		t = t->next;
	}
}

int	main(void)
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
