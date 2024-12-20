/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comandes_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:41:29 by smercado          #+#    #+#             */
/*   Updated: 2024/12/19 14:30:00 by smercado         ###   ########.fr       */
/*   Updated: 2024/12/18 10:16:17 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parse_error(t_command **command, t_lex **list_lex, char *str)
{
	printf("%s\n", str);
	if (command && *command)
		free_comandes(*command);
	if (list_lex && *list_lex)
		free_lex_list(*list_lex);
	exit (-1);
}

void	free_lex_node(t_lex *node)
{
	int	i;

	i = 0;
	if (node->command)
		free(node->command);
	if (node->arguments)
	{
		while (node->arguments[i])
		{
			free(node->arguments[i]);
			i++;
		}
		free(node->arguments);
	}
	free(node);
}

void	free_cmd_node(t_command *cmd) 
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
