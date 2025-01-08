/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:52:22 by ecoma-ba          #+#    #+#             */
/*   Updated: 2025/01/08 13:07:21 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "parsing.h"

/**
 *	Counts the environment variable's name's len.
 *	*str is a pointer to the start of the variable name (not including the '$')
 */
size_t	get_var_len(char *str)
{
	size_t	len;

	len = 0;
	if (*str == '?')
		return (1);
	while (ft_isalnum(str[len]) || str[len] == '_')
		len++;
	return (len);
}

/**
 *	Returns the next environment variable or NULL if not found (or malformed).
 */
char	*get_next_var(char *str)
{
	size_t	len;
	char	*var;

	len = get_var_len(str);
	if (!len)
		return (NULL);
	var = ft_calloc(len + 1, sizeof(char));
	ft_strlcpy(var, str, len + 1);
	return (var);
}

unsigned int	var_count(char *str)
{
	unsigned int	count;
	size_t			i;

	if (!str)
		return (0);
	count = 0;
	i = -1;
	while (str[++i])
		if (str[i] == '$')
			count++;
	return (count);
}
