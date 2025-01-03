/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:41:29 by smercado          #+#    #+#             */
/*   Updated: 2025/01/03 15:55:41 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Frees the memory of a command node, including its arguments,
 * redirections, and files.
 */
void	free_comanda(t_command *cmd)
{
	int	i;

	i = 0;
	if (cmd->arguments)
	{
		while (cmd->arguments[i])
		{
			free(cmd->arguments[i]);
			i++;
		}
		free(cmd->arguments);
	}
	if (cmd->redir)
		free(cmd->redir);
	if (cmd->file)
	{
		i = 0;
		while (cmd->file[i])
		{
			free(cmd->file[i]);
			i++;
		}
		free(cmd->file);
	}
}

void	free_comandes(t_command *command)
{
	t_command	*tmp_com;

	while (command)
	{
		tmp_com = command;
		free_comanda(tmp_com);
		command = command->next;
		free(tmp_com);
	}
}

void	free_strarr(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}
