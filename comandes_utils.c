/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comandes_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smercado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:41:29 by smercado          #+#    #+#             */
/*   Updated: 2024/12/11 12:50:10 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	parse_error(t_comand **comand, t_lex **list_lex, char *str)
{
//	if (comand)
//		free(comand)
	printf("%s\n", str);
	exit (-1);
}
