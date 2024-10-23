/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:08:08 by aarenas-          #+#    #+#             */
/*   Updated: 2024/09/26 16:00:33 by aarenas-         ###   ########.fr       */
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

void	ft_exit(char **argv, t_data *data)
{
	int	error;

	error = 0;
	while (error % 256)
		error /= 256;
	if (!argv[0] && data)
		error = data->error;
	else if (argv[0] && ft_isdigit(*argv[0]) == 0)
		ft_write_exit_error(2);
	else if (argv[0] && ft_isdigit(*argv[0]) == 1 && argv[1])
		ft_write_exit_error(1);
	else if (argv[0] && ft_isdigit(*argv[0]) == 1)
		error = ft_atoi(argv[0]);
	else if (!argv[0])
		error = data->error;
	//si un cmd sale bien entonces error = 0
	//ft_free_data(data);
	exit(error);
}
//hay que inicializar data->error a 0. Quizas al iniciar error en esta
//	funcion no pase nada realmente.
//Antes de poder ejecutar esta funcion hay que limpiar todo lo que hayamos
//	estado usando: t_cmd_list->cmd(de toda la lista), t_data->cmd, cerrar fd.
//Como deberiamos manejar un exit durante la ejecucion de un hijo. Ignorar si
//	exit no es el unico comando recibido.