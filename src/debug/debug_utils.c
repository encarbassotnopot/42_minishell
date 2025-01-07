/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:50:50 by ecoma-ba          #+#    #+#             */
/*   Updated: 2025/01/04 15:53:41 by ecoma-ba         ###   ########.fr       */
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

void	print_operator_line(t_operator_type e)
{
	if (e == LESS)
		printf("<");
	if (e == GREAT)
		printf(">");
	if (e == DLESS)
		printf("<<");
	if (e == DGREAT)
		printf(">>");
	if (e == PIPE)
		printf("|");
}

void	print_tok_type(t_token_type e)
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
