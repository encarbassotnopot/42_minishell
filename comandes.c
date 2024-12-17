/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comandes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smercado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:29:03 by smercado          #+#    #+#             */
/*   Updated: 2024/12/17 11:26:19 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_lex_size(t_lex *lex)
{
	t_lex	*tmp_lex;
	int		i;

	i = 0;
	if (!lex)
		return (0);
	tmp_lex = lex;
	while (tmp_lex)
	{
		i++;
		if (!tmp_lex->next)
			return (i + 1);
		tmp_lex = tmp_lex->next;
	}
	return (i);
}

static t_command	*make_new_command(t_command *com)
{
	t_command	*my_com;

	my_com = ft_calloc(1, sizeof(t_command));
	my_com->word = NULL;
	if (com)
		com->next = my_com;
	return (my_com);
}

static void	add_word(t_lex *lex, t_command **cur_com)
{
	int	i;

	i = 0;
	(*cur_com)->word = ft_strdup(lex->command);
	if (lex->arguments)
	{
		(*cur_com)->arguments = ft_calloc((get_lex_size(lex) + 1), sizeof(char **));
		while (lex->arguments[i])
		{
			(*cur_com)->arguments[i] = ft_strdup(lex->arguments[i]);
			i++;
		}
	}
}

static void	add_redirection(t_lex *lex, t_command **cur_com)
{
	int	i;

	i = 0;
	if (lex->command)
	{
		if (!(*cur_com)->file)
		{
			(*cur_com)->redir = ft_calloc((get_lex_size(lex) + 1), sizeof(t_operator_type));
			(*cur_com)->file = ft_calloc((get_lex_size(lex) + 1) , sizeof(char **));
		}
		while ((*cur_com)->file[i])
			i++;
		(*cur_com)->file[i] = ft_strdup(lex->command);
		(*cur_com)->redir[i] = ft_calloc(1, sizeof(t_operator_type));
		*((*cur_com)->redir[i]) = lex->redir_type;
	}
	else
		printf("error + frees\n");
}

t_command	*redefine_lex(t_lex *list_lex)
{
	t_command	*cur_com;
	t_command	*list_com;
	t_lex		*tmp_lex;

	list_com = make_new_command(NULL);
	cur_com = list_com;
	tmp_lex = list_lex;
	while (tmp_lex)
	{
		if (tmp_lex->type == PIP)
		{
			if ((list_lex == tmp_lex) || (!tmp_lex->next))
				parse_error(&list_com, &list_lex, "parse error near `|'");
			cur_com = make_new_command(cur_com);
		}
		else if (tmp_lex->type == PRINCIPAL_WORD)
			add_word(tmp_lex, &cur_com);
		else
			add_redirection(tmp_lex, &cur_com);
		tmp_lex = tmp_lex->next;
	}
//	free_lex(list_lex);
	return (list_com);
}

void	command_debug(t_command *command)
{
	int i = 1;
	int	j;
	//t_command *temp_c;

	//temp_c = command;
	while (command)
	{
		j = 0;
		printf("\ncomanda %d\n", i);
		printf("paraula principal: %s\n", command->word);
		if (command->arguments)
		{
			while (command->arguments[j])
			{
				printf("argument[%d]: %s\n", j, command->arguments[j]);
				j++;
			}
		}
		if (command->file)
		{
			j = 0;
			while (command->file[j])
			{
				print_operator(*command->redir[j]);
    			printf("file: %s\n", command->file[j]);
				j++;
			}
		}
		command = command->next;
		i++;
	}
}
