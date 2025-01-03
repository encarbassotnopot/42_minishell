/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 11:59:48 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/12/28 15:55:38 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "here_doc.h"

/**
 * Empties and frees a command's here_buf.
 */
void	here_clean(t_command *command)
{
	t_here_buf	*prev;
	t_here_buf	*buf;

	buf = command->here_buf;
	prev = buf;
	while (buf)
	{
		buf = buf->next;
		free(prev->line);
		free(prev);
		prev = buf;
	}
	command->here_buf = NULL;
}

/**
 * Appends a new here_buf struct to the end of the current command's here_buf.
 */
void	here_append(t_command *command, char *line)
{
	t_here_buf	*last_buf;
	t_here_buf	*new_buf;

	new_buf = ft_calloc(1, sizeof(t_here_buf));
	new_buf->line = line;
	if (!new_buf)
		return ;
	if (!command->here_buf)
	{
		command->here_buf = new_buf;
		return ;
	}
	last_buf = command->here_buf;
	while (last_buf->next)
	{
		last_buf = last_buf->next;
	}
	last_buf->next = new_buf;
}

/**
 * Asks for user input until a line matching stop (or EOF) is found.
 * The input is saved in the here_buf list, found inside a command's own struct.
 */
void	here_doc(t_command *command, char *stop)
{
	char	*line;

	here_clean(command);
	line = readline("heredoc > ");
	while (line && ft_strcmp(line, stop) != 0)
	{
		here_append(command, line);
		line = readline("heredoc > ");
	}
	free(line);
}

/**
 * Writes a here_doc's content to a command's input.
 * Frees the here_doc when done.
 */
void	here_feed(t_command *command)
{
	t_here_buf	*buf;
	int			fds[2];

	buf = command->here_buf;
	if (pipe(fds))
		return ;
	overwrite_fd(command, P_READ, fds[P_READ]);
	while (buf)
	{
		write(fds[P_WRITE], buf->line, ft_strlen(buf->line));
		write(fds[P_WRITE], "\n", 1);
		buf = buf->next;
	}
	close(fds[P_WRITE]);
}
