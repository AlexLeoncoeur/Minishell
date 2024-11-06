/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:38:37 by jcallejo          #+#    #+#             */
/*   Updated: 2024/11/06 11:42:12 by jcallejo         ###   ########.fr       */
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
	data->env_variables = 0;
	data->input = 0;
	data->heredoc = 0;
	data->error = 0;
	data->envp = NULL;
	data->cmd = NULL;
	data->exit = 0;
	signal_setter();
	ft_active_setter(0);
	ft_copy_envp(data, envp);
	shell_lvl(data);
	update_name(data);
	return (1);
}
