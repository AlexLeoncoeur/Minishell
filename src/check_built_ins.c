/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built_ins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:14:42 by aarenas-          #+#    #+#             */
/*   Updated: 2024/10/17 13:01:19 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_check_built_ins(t_arg_list *data)
{
	int	i;

	i = 2;
	data->env = ft_lst_env(data->envp, data->env);
	data->env_export = ft_lst_env(data->envp, data->env_export);
	ft_export("A=pipo", data);
	ft_export("ajo=pipo", data);
	if (ft_strncmp(data->argv[1], "env\0", 4) == 0)
		ft_env(data->env);
	else if (ft_strncmp(data->argv[1], "exit\0", 5) == 0)
		ft_exit(&data->argv[2], NULL);
	else if (ft_strncmp(data->argv[1], "echo\0", 5) == 0)
		ft_echo(&data->argv[2]);
	else if (ft_strncmp(data->argv[1], "pwd\0", 4) == 0)
		ft_pwd(data->error);
	else if (ft_strncmp(data->argv[1], "export\0", 7) == 0)
	{
		if (data->argc > 2)
			while (data->argv[i])
				ft_export(data->argv[i++], data);
		else
			ft_export(NULL, data);
	}
	else if (ft_strncmp(data->argv[1], "unset\0", 6) == 0)
	{
		if (data->argv[2])
		{
			ft_unset(data->env, data->argv[2]);
			ft_unset(data->env_export, data->argv[2]);
		}
	}
	ft_export(NULL, data);
	//ft_env(data->env);
	ft_free_data(data);
}
