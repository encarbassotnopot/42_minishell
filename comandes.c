/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comandes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:29:03 by smercado          #+#    #+#             */
/*   Updated: 2024/12/19 11:58:20 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
	return (i + 1);
}

static t_command	*make_new_command(t_command *com)
{
	t_command	*my_com;

	my_com = ft_calloc(1, sizeof(t_command));
	my_com->fds[P_READ] = STDIN_FILENO;
	my_com->fds[P_WRITE] = STDOUT_FILENO;
	if (com)
		com->next = my_com;
	return (my_com);
}

static void	add_word(t_lex *lex, t_command **cur_com)
{
	int	i;

	i = 0;
	(*cur_com)->arguments = ft_calloc((get_lex_size(lex) + 1), sizeof(char *));
	(*cur_com)->arguments[i] = ft_strdup(lex->command);
	if (lex->arguments)
	{
		while (lex->arguments[i])
		{
			(*cur_com)->arguments[i + 1] = ft_strdup(lex->arguments[i]);
			i++;
		}
		(*cur_com)->arguments[i + 1] = ft_strdup(NULL);
	}
}

static void	add_redirection(t_lex *lex, t_lex **list_lex, t_command **cur_com,
		t_command **list_com)
{
	int	i;

	i = 0;
	if (lex->command)
	{
		if (!(*cur_com)->file)
		{
			(*cur_com)->redir = ft_calloc((get_lex_size(lex)),
					sizeof(t_operator_type));
			(*cur_com)->file = ft_calloc((get_lex_size(lex)), sizeof(char **));
		}
		while ((*cur_com)->file[i])
			i++;
		(*cur_com)->file[i] = ft_strdup(lex->command);
		(*cur_com)->redir[i] = ft_calloc(1, sizeof(t_operator_type));
		*((*cur_com)->redir[i]) = lex->redir_type;
	}
	else if ((*list_lex) && (*list_lex)->next)
	{
		if ((*list_lex)->next->type == PIP)
			parse_error(list_com, list_lex, "parse error near `|'");
		parse_error(list_com, list_lex, "parse error near `n'");
	}
	else
		parse_error(list_com, list_lex, "parse error near `n'");
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
		else if (tmp_lex->redir_type != OP_UNSET)
			add_redirection(tmp_lex, &list_lex, &cur_com, &list_com);
		else
			add_word(tmp_lex, &cur_com);
		tmp_lex = tmp_lex->next;
	}
	return (list_com);
}
