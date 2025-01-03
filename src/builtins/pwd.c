/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smercado <smercado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:07:51 by smercado          #+#    #+#             */
/*   Updated: 2025/01/03 18:08:45 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_pwd(t_command *command, t_environment *env)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (!buf)
		return (printf("minishell: pwd: %s\n", strerror(errno)), -1);
	printf("%s\n", buf);
	return (0);
	free(buf);
}
