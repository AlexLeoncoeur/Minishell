/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:38:37 by jcallejo          #+#    #+#             */
/*   Updated: 2024/10/23 10:58:27 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_copy_envp(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	data->envp = malloc (sizeof(char) * ft_strlen(i + 1));
	if (!data->envp)
		return ;
	i = 0;
	while (data->envp[i])
	{
		data->envp[i] = envp[i];
		i++;
	}
	data->envp[i] = NULL;
}

int	ft_init(t_data *data, int argc, char **argv, char **envp)
{
	data->line = NULL;
	data->input = NULL;
	data->heredoc = NULL;
	data->argc = argc;
	data->argv = argv;
	data->redir_err = 0;
	data->status = 0;
	data->exit_status = 0;
	signal_setter();
	ft_active_setter(0);
	ft_copy_envp(data, envp);
	return (1);
}
