/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:07:13 by aarenas-          #+#    #+#             */
/*   Updated: 2024/11/15 10:59:51 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_do_last_cmd(t_cmd *lst, int *builtin_done)
{
	int		child;
	char	*path;

	child = fork();
	if (child == 0)
	{
		ft_check_built_ins(lst, builtin_done);
		if (*builtin_done == 1)
		{
			path = ft_pathfinder(lst->data, lst->path);
			if (execve(path, &lst->argv[1], NULL) < 0)
			{
				perror("minishell: executer");
				free(lst->path);
				ft_free(lst->argv);
				exit(1);
			}
		}
	}
	else if (child == -1)
		perror("Error");
}
