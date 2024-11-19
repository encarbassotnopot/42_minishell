/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smercado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:19:09 by smercado          #+#    #+#             */
/*   Updated: 2024/11/19 10:25:48 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "readline/readline.h"
# include "readline/history.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef enum s_token_type
{
	WORD,
	OPERATOR,
	QUOTE,
} t_token_type;

typedef struct s_token
{
	char			*token_node;
	t_token_type	t_type;
	struct s_token	*next;
} t_token;


# endif
