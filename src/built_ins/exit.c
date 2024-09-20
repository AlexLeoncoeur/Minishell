/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:08:08 by aarenas-          #+#    #+#             */
/*   Updated: 2024/09/20 10:53:28 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit(int error) //o error guardado en estructura
{
	//manejar errores especificos de exit
	if (ft_isdigit(error) != 1)
		error = 2;
	//si el primer agumento es un numero y hay mas arrrrrrgumentos, no sale. too many arguments 1
	//si el primero es letra, sale pero da error numeric argument required 2
	if (error != 0)
		ft_write_error(error);
	exit(error);
}
