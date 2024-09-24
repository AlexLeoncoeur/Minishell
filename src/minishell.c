/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:04:51 by jcallejo          #+#    #+#             */
/*   Updated: 2024/09/24 11:36:53 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	ft_init(&data);
	while (!data.exit_status)
	{
		data.line = readline();
		if (data.line == NULL)
		{
			printf("\n");
			break ;
		}
		if (ft_strcmp(data.line, "") == 0 || ft_is_all_space(data.line))
		{
			free(data.line);
			continue ;
		}
	}
}
