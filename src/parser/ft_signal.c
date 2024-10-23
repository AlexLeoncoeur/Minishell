/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:51:38 by jcallejo          #+#    #+#             */
/*   Updated: 2024/10/23 18:47:05 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	*g_var_on;

void	signal_handler(int signal)
{
	(void) signal;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	if (ft_active_getter() == 0)
		rl_redisplay();
}

void	signal_setter(void)
{
	struct sigaction	sa_ignore;

	sa_ignore.sa_handler = SIG_IGN;
	sigemptyset(&sa_ignore.sa_mask);
	sa_ignore.sa_flags = 0;
	sigaction(SIGQUIT, &sa_ignore, NULL);
	signal(SIGINT, signal_handler);
}

void	ft_active_setter(int i)
{
	static int	g_active;

	g_active = i;
	g_var_on = &g_active;
}

int	ft_active_getter(void)
{
	int	g_active;

	g_active = *g_var_on;
	return (g_active);
}
