/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:04:51 by jcallejo          #+#    #+#             */
/*   Updated: 2024/10/01 10:41:30 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	ft_init(&data, argc, argv, envp);
	while (!data.exit_status)
	{
		data.line = readline("minishell$ ");
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
		ft_parser(&data);
	}
}
