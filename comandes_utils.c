/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comandes_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:41:29 by smercado          #+#    #+#             */
/*   Updated: 2024/12/18 10:22:36 by smercado         ###   ########.fr       */
/*   Updated: 2024/12/18 10:16:17 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parsing.h"

void	parse_error(t_command **command, t_lex **list_lex, char *str)
{
	printf("%s\n", str);
	if (command && *command)
        free_command_list(command);
	if (list_lex && *list_lex)
        free_lex_list(list_lex);
	exit (-1);
}

void free_lex_list(t_lex **list_lex)
{
    t_lex *temp;

    while (*list_lex)
    {
        temp = (*list_lex)->next;
        free_lex_node(*list_lex); 
		*list_lex = temp;
    }
}

void free_command_list(t_command **command)
{
    t_command *temp;

    while (*command)
    {
        temp = (*command)->next;
        free_command_node(*command); 
        *command = temp;
    }
}

void free_lex_node(t_lex *node)
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

void free_command_node(t_command *node)
{
	int	i;

	i = 0;
    if (node->word)
        free(node->word); 
    if (node->arguments)
    {
		while (node->arguments[i])
		{
            free(node->arguments[i]);
			i++;
		}
        free(node->arguments);        
    }
    if (node->redir)
    {
		i = 0;
		while (node->redir[i])
		{
			free(node->redir[i]);
			i++;
		}
        free(node->redir);       
    }
    if (node->file)
    {
		i = 0;
		while (node->file[i])
		{
            free(node->file[i]); 
			i++;
		}
        free(node->file);        
    }
    free(node);
}
/*
void	free_comandes(t_command *command)
{
	t_command	*tmp_com;

	tmp_com = command;
	while (command)
	{
		if (tmp_com->word)
			free(tmp_com->word);
		free_cmd_node(tmp_com);
		free(tmp_com);
		tmp_com = command;
		command = command->next;
	}
//	free(tmp_com->word);
//	free_cmd_node(tmp_com->next);
//	free(tmp_com);
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
*/
