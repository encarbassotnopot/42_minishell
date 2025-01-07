/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smercado <smercado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:14:47 by smercado          #+#    #+#             */
/*   Updated: 2025/01/07 11:28:29 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	count_args(t_command *command)
{
	int arg_count;

	arg_count = 0;
	while (command->arguments[arg_count])
		arg_count++;
	return (arg_count);
}