/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built_ins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:14:42 by aarenas-          #+#    #+#             */
/*   Updated: 2024/11/05 18:41:03 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_check_cd_unset(t_cmd *cmd, int *builtin_done)
{
	int	i;

	i = 0;
	if (ft_strncmp(cmd->cmd, "unset\0", 6) == 0)
	{
		if (cmd->argv)
		{
			while (cmd->argv[i])
			{
				ft_unset(&cmd->env, cmd->argv[i]);
				ft_unset(&cmd->env_export, cmd->argv[i]);
				i++;
			}
		}
	}
	else if (ft_strncmp(cmd->cmd, "cd\0", 3) == 0)
	{
		if (cmd->argv)
			ft_cd(cmd->data, cmd->argv);
		else
			ft_cd(cmd->data, (char **)getenv("HOME"));
	}
	else
		*builtin_done = 1;
}

void	ft_check_built_ins(t_cmd *cmd, int *builtin_done)
{
	int	i;

	i = 2;
	*builtin_done = 0;
	cmd->env = ft_lst_env(cmd->envp, cmd->env);
	cmd->env_export = ft_lst_env(cmd->envp, cmd->env_export);
	if (ft_strncmp(cmd->cmd, "env\0", 4) == 0)
		ft_env(cmd->env);
	else if (ft_strncmp(cmd->cmd, "exit\0", 5) == 0)
		ft_exit(cmd->argv, NULL);
	else if (ft_strncmp(cmd->cmd, "echo\0", 5) == 0)
		ft_echo(cmd->argv);
	else if (ft_strncmp(cmd->cmd, "pwd\0", 4) == 0)
		ft_pwd(cmd->data);
	else if (ft_strncmp(cmd->cmd, "export\0", 7) == 0)
	{
		if (cmd->argv)
			while (cmd->argv[i])
				ft_export(cmd->argv[i++], cmd);
		else
			ft_export(NULL, cmd);
	}
	else
		ft_check_cd_unset(cmd, builtin_done);
}

	//ft_free_data(data); estoy hay que ponerlo cuando termine el programa