/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:04:51 by jcallejo          #+#    #+#             */
/*   Updated: 2024/11/07 11:15:03 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_delete_heredoc(void)
{
	int	fd;

	fd = open(".heredoc_tmp", O_RDONLY);
	if (fd > 0)
		unlink(".heredoc_tmp");
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	ft_init(&data, argc, argv, envp);
	while (data.exit != 1)
	{
		if (ft_read_string(&data))
		{
			data.cmd = ft_parser(&data);
			if (data.cmd)
			{
				ft_set_flag(1);
				//aqui deberia ir el executer
				ft_delete_heredoc();
				ft_clean_cmd(&data);
			}
		}
		ft_set_flag(0);
	}
}
