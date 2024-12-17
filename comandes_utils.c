/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comandes_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:41:29 by smercado          #+#    #+#             */
/*   Updated: 2024/12/17 13:17:25 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parsing.h"

void	parse_error(t_command **command, t_lex **list_lex, char *str)
{
//	if (command)
//		free(command)
	printf("%s\n", str);
	exit (-1);
}
