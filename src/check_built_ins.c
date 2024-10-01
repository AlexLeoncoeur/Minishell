/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built_ins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:14:42 by aarenas-          #+#    #+#             */
/*   Updated: 2024/10/01 15:14:46 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_check_built_ins(t_arg_list *lst)
{
	t_env	*env;

	env = ft_lst_env(lst->envp);
	if (ft_strncmp(lst->argv[1], "env\0", 4) == 0)
		ft_env(env);
	else if (ft_strncmp(lst->argv[1], "exit\0", 5) == 0)
		ft_exit(&lst->argv[2], NULL);
	else if (ft_strncmp(lst->argv[1], "echo\0", 5) == 0)
		ft_echo(&lst->argv[2]);
	else if (ft_strncmp(lst->argv[1], "pwd\0", 4) == 0)
	{
		//ft_pwd(data);
	}
}
