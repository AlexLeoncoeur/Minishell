/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:04:51 by jcallejo          #+#    #+#             */
/*   Updated: 2024/11/25 15:07:21 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	ft_void(void)
// {
// 	system("leaks -q minishell");
// }

static void	ft_delete_heredoc(void)
{
	int	fd;

	fd = open(".heredoc_tmp", O_RDONLY);
	if (fd > 0)
		unlink(".heredoc_tmp");
}

//atexit(ft_void);

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	ft_init(&data, envp);
	(void)argc;
	(void)argv;
	while (data.error == 0)
	{
		if (ft_read_string(&data))
		{
			if (*data.input)
			{
				data.cmd = ft_parser(&data);
				if (data.cmd)
				{
					ft_set_flag(1);
					ft_executer(&data);
					ft_delete_heredoc();
					ft_clean_cmd(&data);
				}
			}
		}
		ft_set_flag(0);
	}
	return (free(data.input), data.error);
}
