/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:08:08 by aarenas-          #+#    #+#             */
/*   Updated: 2024/09/23 16:05:55 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_write_exit_error(int error)
{
	if (error == 1)
		ft_putstr("minishell: exit: too many arguments\n");
	else if (error == 2)
		ft_putstr("minishell: exit: numeric argument required\n");
}

void	ft_exit(char **argv, t_data *data) //o error guardado en estructura
{
	int	error;

	error = 0;
	if (!argv[0] && data)
		error = data->error;
	//manejar errores especificos de exit
	else if (argv[0] && ft_isdigit(*argv[0]) == 0)
		error = 2;
	else if (argv[0] && ft_isdigit(*argv[0]) == 1 && argv[1])
		error = 1;
	//si el primer agumento es un numero y hay mas arrrrrrgumentos, no sale. too many arguments 1
	//si el primero es letra, sale pero da error numeric argument required 2
	//si un cmd sale bien entonces error = 0
	if (error != 0)
		ft_write_exit_error(error);
	exit(error);
}
