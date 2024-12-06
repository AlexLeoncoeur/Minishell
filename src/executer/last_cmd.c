/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:07:13 by aarenas-          #+#    #+#             */
/*   Updated: 2024/12/04 15:58:53 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_do_last_cmd(t_cmd *lst, int *builtin_done)
{
	int		child;
	char	*path;

	child = fork();
	if (child == -1)
		perror("Error");
	else if (child == 0)
	{
		ft_check_built_ins(lst, builtin_done);
		if (*builtin_done == 1)
		{
			if (!ft_strncmp(lst->path, "/", 1))
				path = lst->path;
			else
				path = ft_pathfinder(lst->data, lst->path);
			if (execve(path, lst->argv, lst->data->envp) < 0)
			{
				perror("minishell: executer");
				ft_exit(NULL, lst->data);
			}
		}
		ft_exit(NULL, lst->data);
	}
	ft_wait(&lst->data->error);
}