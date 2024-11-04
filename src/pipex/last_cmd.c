/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:07:13 by aarenas-          #+#    #+#             */
/*   Updated: 2024/11/04 12:09:31 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_do_last_cmd(t_cmd *lst)
{
	int	child;

	child = fork();
	if (child == 0)
	{
		if (execve(lst->cmd, lst->argv, lst->env) < 0)
		{
			ft_free(lst->argv);
			free(lst);
			perror("Error");
			exit (1);
		}
	}
	else if (child == -1)
		perror("Error");
}
