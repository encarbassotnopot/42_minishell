/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:41:29 by smercado          #+#    #+#             */
/*   Updated: 2025/01/03 17:13:57 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_strarr(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}
/**
 * Frees the memory of a command node, including its arguments,
 * redirections, and files.
 */
void	free_comanda(t_command **comanda)
{
	t_command	*cmd;

	if (!*comanda)
		return ;
	cmd = *comanda;
	if (cmd->arguments)
		free_strarr(cmd->arguments);
	if (cmd->redir)
		free(cmd->redir);
	if (cmd->file)
		free_strarr(cmd->file);
	*comanda = NULL;
}

void	free_comandes(t_command **command)
{
	t_command	*tmp_com;
	t_command	*my_com;

	if (!command)
		return ;
	my_com = *command;
	while (my_com)
	{
		tmp_com = my_com;
		free_comanda(&tmp_com);
		my_com = my_com->next;
		free(tmp_com);
	}
	*command = NULL;
}
