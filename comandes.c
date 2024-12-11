/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comandes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smercado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:29:03 by smercado          #+#    #+#             */
/*   Updated: 2024/12/11 13:20:29 by smercado         ###   ########.fr       */
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

static t_comand	*make_new_comand(t_comand *com)
{
	t_comand	*my_com;

	my_com = ft_calloc(1, sizeof(t_comand));
	my_com->word = NULL;
	if (com)
		com->next = my_com;
	return (my_com);
}

static void	add_word(t_lex *lex, t_comand **cur_com)
{
	int	i;

	i = 0;
	(*cur_com)->word = ft_strdup(lex->comand);
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

static void	add_redirection(t_lex *lex, t_comand **cur_com)
{
	int	i;

	i = 0;
	if (lex->comand)
	{
		if (!(*cur_com)->file)
		{
			(*cur_com)->redir = ft_calloc((get_lex_size(lex) + 1), sizeof(t_operator_type));
			(*cur_com)->file = ft_calloc((get_lex_size(lex) + 1) , sizeof(char **));
		}
		while ((*cur_com)->file[i])
			i++;
		(*cur_com)->file[i] = ft_strdup(lex->comand);
		(*cur_com)->redir[i] = ft_calloc(1, sizeof(t_operator_type));
		*((*cur_com)->redir[i]) = lex->redir_type;
	}
	else
		printf("error + frees\n");
}

t_comand	*redefine_lex(t_lex *list_lex)
{
	t_comand	*cur_com;
	t_comand	*list_com;
	t_lex		*tmp_lex;

	list_com = make_new_comand(NULL);
	cur_com = list_com;
	tmp_lex = list_lex;
	while (tmp_lex)
	{
		if (tmp_lex->type == PIP)
		{
			if ((list_lex == tmp_lex) || (!tmp_lex->next))
				parse_error(&list_com, &list_lex, "parse error near `|'");
			cur_com = make_new_comand(cur_com);
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

void	comand_debug(t_comand *comand)
{
	int i = 1;
	int	j;

	while (comand)
	{
		j = 0;
		printf("\ncomanda %d\n", i);
		printf("paraula principal: %s\n", comand->word);
		if (comand->arguments)
		{
			while (comand->arguments[j])
			{
				printf("argument[%d]: %s\n", j, comand->arguments[j]);
				j++;
			}
		}
		if (comand->file)
		{
			j = 0;
			while (comand->file[j])
			{
				print_operator(*comand->redir[j]);
    			printf("file: %s\n", comand->file[j]);
				j++;
			}
		}
		comand = comand->next;
		i++;
	}
}
