/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:51:33 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/12/27 16:37:47 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*get_exe(char *path, char *name)
{
	char	**paths;
	char	*file;
	int		i;

	i = -1;
	paths = ft_split(path, ':');
	if (!paths)
		pexit("split");
	while (paths[++i])
	{
		file = ft_strjoins(3, paths[i], "/", name);
		if (access(file, X_OK) == 0)
			break ;
		free(file);
	}
	if (!paths[i])
		file = NULL;
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (file);
}

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
 *  Tries to open or create a file for (truncated) writing.
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
 * fd_type must be P_READ or P_WRITE
 */
int	overwrite_fd(t_command *cmd, int fd_type, int new_fd)
{
	int	ret;

	ret = 0;
	if (fd_type == P_WRITE && cmd->fds[P_WRITE] != STDOUT_FILENO)
		ret = close(cmd->fds[P_WRITE]);
	if (fd_type == P_READ && cmd->fds[P_READ] != STDIN_FILENO)
		ret = close(cmd->fds[P_READ]);
	if (fd_type == P_READ)
		cmd->fds[P_READ] = new_fd;
	else if (fd_type == P_WRITE)
		cmd->fds[P_WRITE] = new_fd;
	return (ret);
}

/**
 * Iterates through a command's redirections and sets them up.
 * Returns -1 on error, 0 otherwise.
 */
int	setup_redirs(t_command *command)
{
	size_t	i;
	int		fd;

	i = -1;
	if (!command->redir)
		return (0);
	while (command->redir[++i] && command->file[i])
	{
		if (command->redir[i] == LESS)
			fd = redir_read(command->file[i]);
		else if (command->redir[i] == GREAT)
			fd = redir_trunc(command->file[i]);
		else if (command->redir[i] == DGREAT)
			fd = redir_append(command->file[i]);
		if (fd == -1)
			return (-1);
		if (command->redir[i] == LESS)
			overwrite_fd(command, P_READ, fd);
		else
			overwrite_fd(command, P_WRITE, fd);
	}
	return (0);
}

/**
 * Runs the given command.
 * This function should only be called by the child resulting from a fork.
 *
 *
 * Edge case: a command might not even contain a command,
 * and thus be made up only of redirections.
 * In this case, we will set up all the redirections, but we won't call execve.
 */
void	run_command(t_command *command, char **envp)
{
	char	*fp;
	int		ret;

	ret = 0;
	if (setup_redirs(command) == -1)
		pexit("redir");
	if (dup2(command->fds[P_READ], STDIN_FILENO) == -1)
		pexit("dup2 stdin");
	if (dup2(command->fds[P_WRITE], STDOUT_FILENO) == -1)
		pexit("dup2 stdout");
	if (command->arguments[0] && !ft_strchr(command->arguments[0], '/'))
		fp = get_exe(getenv("PATH"), command->arguments[0]);
	else
		fp = command->arguments[0];
	if (fp)
		if (execve(fp, command->arguments, envp))
			ret = -1;
	close(command->fds[P_READ]);
	close(command->fds[P_WRITE]);
	exit(ret);
}

/**
 * Runs a list of commands (pipeline). Returns the number of commands run.
 */
int	run_commands(t_command *command, char **envp)
{
	int		count;
	int		my_pipe[2];
	pid_t	pid;

	count = 0;
	while (command->next)
	{
		if (pipe(my_pipe) == -1)
			pexit("pipe");
		command->fds[P_WRITE] = my_pipe[P_WRITE];
		command->next->fds[P_READ] = my_pipe[P_READ];
		pid = fork();
		if (pid == -1)
			pexit("fork");
		else if (pid == 0)
		{
			run_command(command, envp);
		}
		count++;
		if (command->fds[P_WRITE] != STDOUT_FILENO)
			close(command->fds[P_WRITE]);
		if (command->fds[P_READ] != STDIN_FILENO)
			close(command->fds[P_READ]);
		command = command->next;
	}
	pid = fork();
	if (pid == -1)
		pexit("fork");
	else if (pid == 0)
	{
		run_command(command, envp);
		if (command->fds[P_WRITE] != STDOUT_FILENO)
			close(command->fds[P_WRITE]);
		if (command->fds[P_READ] != STDIN_FILENO)
			close(command->fds[P_READ]);
	}
	if (command->fds[P_WRITE] != STDOUT_FILENO)
		close(command->fds[P_WRITE]);
	if (command->fds[P_READ] != STDIN_FILENO)
		close(command->fds[P_READ]);
	return (count + 1);
}
