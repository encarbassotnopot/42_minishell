/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 10:48:05 by ecoma-ba          #+#    #+#             */
/*   Updated: 2025/01/08 10:49:28 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "here_doc.h"

/**
 * Atempts opening a file for reading.
 * Returns its fd or -1 on error.
 */
int	redir_read(char *file)
{
	int	fd;

	if (access(file, R_OK) == -1)
	{
		perror("couldn't access file for reading");
		return (-1);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
		perror("couldn't open file for reading");
	return (fd);
}

/**
 * Tries to open or create a file for (truncated) writing.
 * Returns its fd or -1 on error.
 */
int	redir_trunc(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		perror("couldn't open/create file for writing");
	return (fd);
}

/**
 * Tries to open or create a file for writing, appending text to the end.
 * Returns its fd or -1 on error.
 */
int	redir_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		perror("couldn't open/create file for writing");
	return (fd);
}

/**
 * Overwrites a command's fd and closes the old one.
 * Doesn't close std fds and returns the close value.
 * fd_type must be P_READ or P_WRITE.
 *
 * If the new_fd is STDIN_FILENO and fd_type is P_READ we assume a here_doc
 * was encountered. Otherwise we will make sure the here_doc content's is empty.
 */
int	overwrite_fd(t_command *cmd, int fd_type, int new_fd)
{
	int	ret;

	ret = 0;
	if (fd_type == P_WRITE && cmd->fds[P_WRITE])
		ret = close(cmd->fds[P_WRITE]);
	if (fd_type == P_READ && cmd->fds[P_READ])
		ret = close(cmd->fds[P_READ]);
	if (fd_type == P_READ)
		cmd->fds[P_READ] = new_fd;
	else if (fd_type == P_WRITE)
		cmd->fds[P_WRITE] = new_fd;
	return (ret);
}

/**
 * Closes a command's fds. Ignores errors. Won't close STDIN/STDOUT
 */
void	cmd_fd_close(t_command *command)
{
	if (command)
	{
		if (command->fds[P_WRITE] != STDOUT_FILENO)
			close(command->fds[P_WRITE]);
		if (command->fds[P_READ] != STDIN_FILENO)
			close(command->fds[P_READ]);
	}
}
