/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:07:13 by aarenas-          #+#    #+#             */
/*   Updated: 2024/12/04 13:43:25 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_do_executable(t_data *data, char *command)
{
	char	*pwd;
	char	*executable;
	char	**route;
	int		i;

	i = ft_strlen(command);
	pwd = getcwd(NULL, 0);
	route = NULL;
	while (i >= 0 && command[i] != '/')
		i--;
	if (command[i] == '/')
	{
		executable = ft_substr(&command[i + 1], 0, ft_strlen(&command[i]));
		route = malloc(sizeof(char *) * 2);
		if (!route)
			return (NULL);
		route[0] = ft_substr(command, 0,
				(ft_strlen(command) - ft_strlen(&command[i])));
		route[i] = NULL;
		ft_cd(data, route);
		dprintf(2, "route: %s\n executable: %s\n", route[0], executable);
		return (executable);
	}
	return (dprintf(2, "minishell: executer: %s: command not found\n", command),
		data->error = 127, ft_exit(NULL, data), NULL);
}

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
