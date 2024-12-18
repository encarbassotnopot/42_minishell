/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:51:33 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/12/18 10:02:53 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*get_exe(char *path, char *name)
{
	char	**paths;
	char	*file;
	int		i;

	i = -1;
	if (ft_strchr(name, '/'))
		return (name);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
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

pid_t	run_commands(t_command *command, char **envp)
{
	pid_t pid_child;
	char *fp;

	pid_child = fork();
	if (pid_child == -1)
		return (0);
	else if (pid_child == 0)
	{
		if (!ft_strchr(command->arguments[0], '/'))
			fp = get_exe(getenv("PATH"), command->arguments[0]);
		else
			fp = command->arguments[0];
		printf("path: %s\n", fp);
		execve(fp, command->arguments, envp);
		exit(1);
	}
	return (pid_child);
}
