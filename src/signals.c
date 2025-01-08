/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smercado <smercado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 08:38:54 by smercado          #+#    #+#             */
/*   Updated: 2025/01/08 12:54:49 by smercado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal;

void	run_signint(int sig)
{
	(void)sig;
	rl_on_new_line();
	printf("\n");
	rl_replace_line("", 0);
	rl_redisplay();
}

void	display_new_line(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
}

void	set_heresign(int sig)
{
	g_signal = sig;
}

void	interactive_signals(void)
{
	signal(SIGINT, run_signint);
	signal(SIGQUIT, SIG_IGN);
}

void	non_interactive_signals(void)
{
	signal(SIGINT, display_new_line);
	signal(SIGQUIT, display_new_line);
}

void	here_signals(void)
{
	g_signal = 0;
	signal(SIGINT, set_heresign);
	signal(SIGQUIT, set_heresign);
}
