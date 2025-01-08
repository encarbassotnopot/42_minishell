/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:51:33 by ecoma-ba          #+#    #+#             */
/*   Updated: 2025/01/08 13:55:08 by ecoma-ba         ###   ########.fr       */
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
		fp = ft_strdup(command->arguments[0]);
	return (fp);
}
