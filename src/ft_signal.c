/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:51:38 by jcallejo          #+#    #+#             */
/*   Updated: 2024/11/21 12:17:53 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	g_signal_flag = 0;

static void	handler_int(int signal)
{
	(void) signal;
	ft_putendl_fd("", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	if (g_signal_flag == 0)
		rl_redisplay();
}

void	ft_set_flag(int i)
{
	g_signal_flag = i;
}

void	ft_init_signals(void)
{
	signal(SIGINT, handler_int);
	signal(SIGQUIT, SIG_IGN);
}
