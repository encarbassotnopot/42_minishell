/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:26:31 by ecoma-ba          #+#    #+#             */
/*   Updated: 2025/01/03 15:55:51 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	pexit(char *error)
{
	perror(error);
	exit(EXIT_FAILURE);
}

int	my_perror(char *error, int ret)
{
	perror(error);
	return (ret);
}
