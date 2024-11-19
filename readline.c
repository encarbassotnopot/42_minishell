/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smercado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:12:52 by smercado          #+#    #+#             */
/*   Updated: 2024/11/19 10:49:58 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


enum operators {"<", ">", "|", "<<", ">>", "&"};
enum quotes {""", "'"};

int	main(int arc, char **argv)
{
	char *line;

	while (1)
	{
		line = readline("minishel_test1: ");
		printf("line is: %s", line);

	//errors_checker
		if (!line)
			break ;
		if (*line)
		{
			add_history(line);
			tokenization(line);
		}
		free(line);
	}
	exit (0);
}

void tokenization(char *line)
{
	char	buffer[99999];
	t_token	*token;
	t_token_type current_type;
	int		i;
	char	c;

	i = 0;
	token = NULL;
	current_type = WORD;
	while (line[i] != '\0')
	{
		if (line[i + 1] == '\0' && buffer[i] != '\0')
		{
			buffer[i] = line[i];
			buffer[i + 1] = '\0';
		//	add_token();
		}
		if (is_operator(line[i]) && (!is_quote(line[i]) && (line[i] == operators))
				//check if tokens se pueden unir y funcionan juntos
				act_token = ft_strjoin(act_token, (char *)line[i]);
		if 
	}

}

