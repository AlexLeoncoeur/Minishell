/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:38:37 by jcallejo          #+#    #+#             */
/*   Updated: 2024/11/07 11:18:49 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	shell_lvl(t_data *data)
{
	char	*lvl;
	char	*str;
	char	*aux;
	int		i;

	lvl = ft_get_env(data, "SHLVL")->value;
	i = ft_atoi(lvl) + 1;
	lvl = ft_itoa(i);
	aux = ft_strdup("SHLVL=");
	str = ft_strjoin(aux, lvl);
	ft_export(str, data);
	free(lvl);
	free(aux);
	free(str);
	ft_cd(data, NULL);
}

static void	update_name(t_data *data)
{
	char	*name;
	char	*str;
	char	*aux;

	aux = ft_strdup("SHELL=");
	name = ft_strdup("minishell");
	str = ft_strjoin(aux, name);
	ft_export(str, data);
	free(str);
	free(name);
	free(aux);
}

int	ft_init(t_data *data, int argc, char **argv, char **envp)
{
	data->env_variables = 0;
	data->cmd = NULL;
	data->input = 0;
	data->heredoc = 0;
	data->error = 0;
	data->envp = NULL;
	data->exit = false;
	ft_init_signals();
	while (*envp)
		ft_export(*envp++, data);
	shell_lvl(data);
	update_name(data);
	return (1);
}
