/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built_ins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:14:42 by aarenas-          #+#    #+#             */
/*   Updated: 2024/10/03 19:24:48 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_check_built_ins(t_arg_list *lst)
{
	ft_lst_env(lst);
	if (ft_strncmp(lst->argv[1], "env\0", 4) == 0)
		ft_env(lst->env);
	else if (ft_strncmp(lst->argv[1], "exit\0", 5) == 0)
		ft_exit(&lst->argv[2], NULL);
	else if (ft_strncmp(lst->argv[1], "echo\0", 5) == 0)
		ft_echo(&lst->argv[2]);
	else if (ft_strncmp(lst->argv[1], "pwd\0", 4) == 0)
	{
		//ft_pwd(data);
	}
	else if (ft_strncmp(lst->argv[1], "export\0", 7) == 0)
		ft_export(lst->argv[2], lst);
}