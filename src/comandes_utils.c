/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comandes_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:29:03 by smercado          #+#    #+#             */
/*   Updated: 2025/01/08 13:59:47 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Calculates and returns the size of the lex,
 * counting the space for the main word and arguments.
 */
int	get_arg_size(t_lex *lex)
{
	int	i;

	i = 0;
	if (!lex)
		return (0);
	if (lex->arguments)
	{
		while (lex->arguments[i])
			i++;
	}
	return (i + 1);
}

/**
 * Counts how many redirections a command has.
 */
int	get_redir_size(t_lex *lex)
{
	int	i;

	i = 0;
	while (lex && lex->type != PIP)
	{
		if (lex->redir_type != OP_UNSET)
			i++;
		lex = lex->next;
	}
	return (i);
}

/**
 * Creates and returns a new command.
 */
t_command	*make_new_command(t_command *com, int arg_size, int redir_size)
{
	t_command	*my_com;

	my_com = ft_calloc(1, sizeof(t_command));
	if (!my_com)
		return (NULL);
	my_com->fds[P_READ] = STDIN_FILENO;
	my_com->fds[P_WRITE] = STDOUT_FILENO;
	my_com->arguments = ft_calloc(arg_size + 1, sizeof(char *));
	if (redir_size != 0)
	{
		my_com->redir = ft_calloc(redir_size + 1, sizeof(t_operator_type *));
		my_com->file = ft_calloc(redir_size + 1, sizeof(char *));
	}
	if (com)
		com->next = my_com;
	return (my_com);
}

/**
 * Allocates memory and adds a main word and its arguments to the new command,
 * without distinguishing between words or arguments
 * and placing them all in the same array.
 */
void	add_word(t_lex *lex, t_command *cur_com)
{
	int	i;

	i = 0;
	cur_com->arguments[i] = ft_strdup(lex->command);
	while (lex->arguments && lex->arguments[i])
	{
		cur_com->arguments[i + 1] = ft_strdup(lex->arguments[i]);
		i++;
	}
}

/**
 * Adds a redirection to the redirection array,
 * assigning the file and the corresponding redirection type.
 * If no valid redirection is found, it throws an error.
 */
void	add_redirection(t_lex *lex, t_command *cur_com)
{
	int	i;

	i = 0;
	while (cur_com->file[i])
	{
		i++;
	}
	cur_com->file[i] = ft_strdup(lex->command);
	cur_com->redir[i] = lex->redir_type;
}
