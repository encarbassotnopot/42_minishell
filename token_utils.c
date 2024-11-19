/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smercado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:39:48 by smercado          #+#    #+#             */
/*   Updated: 2024/11/19 10:48:06 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//false = 0, true = 1


int	is_operator(char c)
{
	if (!c || c != "<" || c != ">" || c != "|" || c != "<<" || c != ">>" || c != "&")
		return (0)
	return (1);
}

int	is_blanck(char c)
{
	if (c == " " || c == '\t')
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == "'" || c == '"')
		return (1);
	return (0);
}
