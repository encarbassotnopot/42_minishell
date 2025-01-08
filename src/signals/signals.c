/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 08:38:54 by smercado          #+#    #+#             */
/*   Updated: 2025/01/08 13:05:13 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

int		g_signal;

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
