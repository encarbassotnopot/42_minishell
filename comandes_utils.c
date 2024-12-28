/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comandes_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smercado <smercado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:41:29 by smercado          #+#    #+#             */
/*   Updated: 2024/12/28 12:32:41 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parsing.h"

/**
 * Prints an error message.
 */
void	parse_error(char *str)
{
	printf("%s\n", str);
}

/**
 * Frees the memory of a lex node, including its command and arguments.
 */
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

/**
 * Frees the memory of a command node, including its arguments, redirections, and files.
 */
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
