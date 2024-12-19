/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:51:33 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/12/19 12:24:59 by ecoma-ba         ###   ########.fr       */
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
 * Runs the given command and sets up its redirections.
 * This function should only be called by the child resulting from a fork.
 *
 * Edge case: a command might not even contain a command,
 * and thus be made up only of redirections.
 * In this case, we will set up all the redirections, but we won't call execve.
 */
void	run_command(t_command *command, char **envp)
{
	char	*fp;

	if (dup2(command->fds[P_READ], STDIN_FILENO) == -1)
		pexit("dup2 stdin");
	if (dup2(command->fds[P_WRITE], STDOUT_FILENO) == -1)
		pexit("dup2 stdout");
	if (command->arguments[0] && !ft_strchr(command->arguments[0], '/'))
		fp = get_exe(getenv("PATH"), command->arguments[0]);
	else
		fp = command->arguments[0];
	if (fp)
		execve(fp, command->arguments, envp);
	close(command->fds[P_READ]);
	close(command->fds[P_WRITE]);
	exit(0);
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
	}
	return (count + 1);
}
