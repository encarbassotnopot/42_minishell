/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:51:33 by ecoma-ba          #+#    #+#             */
/*   Updated: 2025/01/07 14:49:15 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "execution.h"
#include "here_doc.h"

char	*get_exe(const char *path, char *name)
{
	char	**paths;
	char	*file;
	int		i;

	i = -1;
	if (!path)
		return (NULL);
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
 * Iterates through a command's redirections and sets them up.
 * Returns -1 on error, 0 otherwise.
 * When a here_doc is encountered no fd is set up, as the here_feed
 * function will handle it.
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
		{
			fd = redir_read(command->file[i]);
			here_clean(command);
		}
		else if (command->redir[i] == GREAT)
			fd = redir_trunc(command->file[i]);
		else if (command->redir[i] == DGREAT)
			fd = redir_append(command->file[i]);
		else if (command->redir[i] == DLESS)
			here_doc(command, command->file[i]);
		if (command->redir[i] == LESS)
			overwrite_fd(command, P_READ, fd);
		else if (command->redir[i] != DLESS)
			overwrite_fd(command, P_WRITE, fd);
	}
	return (0);
}

/**
 * Gets the command's executable's full path.
 * If it is not found, prints error to stderr and sets the return value to -1.
 */
char	*get_fp(t_command *command, t_environment *env, int *ret)
{
	char	*fp;

	if (!command->arguments[0])
		return (NULL);
	if (!ft_strchr(command->arguments[0], '/'))
	{
		fp = get_exe(get_const_env_value(env, "PATH"), command->arguments[0]);
		if (!fp)
		{
			ft_putstr_fd("Command not found: ", STDERR_FILENO);
			ft_putstr_fd(command->arguments[0], STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
			*ret = -1;
		}
	}
	else
		fp = command->arguments[0];
	return (fp);
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
void	run_command(t_command *command, t_environment *env, t_shell *shinfo)
{
	char	*fp;
	int		ret;
	char	**envp;

	ret = 0;
	if (setup_redirs(command) == -1)
		pexit("redir");
	if (command->here_buf)
		here_feed(command);
	if (dup2(command->fds[P_READ], STDIN_FILENO) == -1)
		pexit("dup2 stdin");
	if (dup2(command->fds[P_WRITE], STDOUT_FILENO) == -1)
		pexit("dup2 stdout");
	if (is_builtin(command))
		ret = run_builtin(command, env, shinfo);
	else
	{
		envp = gen_env(env);
		fp = get_fp(command, env, &ret);
		if (fp)
			if (execve(fp, command->arguments, envp))
				ret = -1;
		free_strarr(envp);
	}
	cleanup(shinfo, NULL, ret);
}

/**
 * Runs a list of commands (pipeline).
 * Returns the exit status of the last command.
 */
int	run_pipeline(t_command *command, t_environment *env, t_shell *shinfo)
{
	int	my_pipe[2];
	int	exit;

	while (command->next)
	{
		if (pipe(my_pipe) == -1)
			return (my_perror("pipe", -1));
		command->fds[P_WRITE] = my_pipe[P_WRITE];
		command->next->fds[P_READ] = my_pipe[P_READ];
		command->pid = fork();
		if (command->pid == -1)
			return (my_perror("fork", -2));
		else if (command->pid == 0)
			run_command(command, env, shinfo);
		cmd_fd_close(shinfo->command);
		command = command->next;
	}
	command->pid = fork();
	if (command->pid == -1)
		return (my_perror("pipe", -1));
	else if (command->pid == 0)
		run_command(command, env, shinfo);
	cmd_fd_close(shinfo->command);
	while (command)
	{
		waitpid(command->pid, &exit, 0);
		command = command->next;
	}
	return (exit);
}

int	run_commands(t_command *command, t_environment *env, t_shell *shinfo)
{
	if (command->next || !is_raw_builtin(command))
		return (run_pipeline(command, env, shinfo));
	else
		return (run_builtin(command, env, shinfo));
}
