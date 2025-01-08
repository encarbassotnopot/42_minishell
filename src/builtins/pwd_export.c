/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:07:51 by smercado          #+#    #+#             */
/*   Updated: 2025/01/08 10:00:17 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

int	run_export(t_shell *sh)
{
	int		arg_count;
	int		i;
	char	*equal;
	char	*name_var;
	char	*value;

	i = 1;
	arg_count = count_args(sh->command);
	if (arg_count == 1)
		return (run_env(sh));
	while (arg_count > i)
	{
		equal = ft_strchr(sh->command->arguments[i], '=');
		if (equal)
		{
			name_var = ft_substr(sh->command->arguments[i], 0, equal
					- sh->command->arguments[i]);
			value = ft_strdup(equal + 1);
			set_env_value(&sh->env, name_var, value);
			free(name_var);
			free(value);
		}
		i++;
	}
	return (0);
}

int	run_pwd(t_shell *sh)
{
	char	*buf;

	(void)sh;
	buf = getcwd(NULL, 0);
	if (!buf)
		return (printf("minishell: pwd: %s\n", strerror(errno)), -1);
	printf("%s\n", buf);
	free(buf);
	return (0);
}
