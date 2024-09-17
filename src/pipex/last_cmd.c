/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:07:13 by aarenas-          #+#    #+#             */
/*   Updated: 2024/09/17 11:34:23 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_do_last_cmd(t_arg_list *lst, int fd)
{
	int	child;
	int	cmd;

	cmd = lst->argc - 2;
	child = fork();
	if (child == 0)
	{
		if (execve(ft_pathfinder(lst, cmd), lst->flags, lst->envp) < 0)
		{
			ft_free(lst->flags);
			free(lst);
			close(fd);
			perror("Error");
			exit (1);
		}
	}
	else if (child == -1)
		perror("Error");
}
