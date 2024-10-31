/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:04:51 by jcallejo          #+#    #+#             */
/*   Updated: 2024/10/29 10:39:16 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	ft_init(&data, argc, argv, envp);
	while (data.exit != 1)
	{
		if (ft_read_string(&data))
		{
			data.cmd = ft_parsecmd(&data);
		}
	}
}
