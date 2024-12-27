/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smercado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 08:38:54 by smercado          #+#    #+#             */
/*   Updated: 2024/12/27 11:46:54 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_signals(void)
{
	signal(SIGINT, run_signint);
	signal(SIGQUIT, SIG_IGN);
}

void	run_signint(int sig)
{
	(void)sig;
	
	
	rl_on_new_line();
	printf("\n");
	rl_replace_line("", 0);
	rl_redisplay();
	signal(SIGQUIT, SIG_IGN);
}

void	run_sigquit(int sig)
{
	signal(SIGQUIT, SIG_IGN);
	printf("Quit (core dumped)\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}
