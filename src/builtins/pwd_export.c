/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smercado <smercado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:07:51 by smercado          #+#    #+#             */
/*   Updated: 2025/01/07 13:10:00 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_export(t_command *command, t_environment *env, t_shell *shinfo)
{
	int		arg_count;
	int		i;
	char	*equal;
	char	*name_var;
	char	*value;

	i = 1;
	arg_count = count_args(command);
	if (arg_count == 1)
		print_env(env);
	while (arg_count > i)
	{
		equal = ft_strchr(command->arguments[i], '=');
		if (equal)
		{
			name_var = ft_substr(command->arguments[i], 0, equal
					- command->arguments[i]);
			value = ft_strdup(equal + 1);
			set_env_value(&env, name_var, value);
			free(name_var);
			free(value);
		}
		i++;
	}
	return (0);
}

int	run_pwd(t_command *command, t_environment *env, t_shell *shinfo)
{
	char	*buf;

	(void)env;
	(void)command;
	(void)shinfo;
	buf = getcwd(NULL, 0);
	if (!buf)
		return (printf("minishell: pwd: %s\n", strerror(errno)), -1);
	printf("%s\n", buf);
	free(buf);
	return (0);
}
