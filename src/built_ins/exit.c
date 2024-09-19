/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:08:08 by aarenas-          #+#    #+#             */
/*   Updated: 2024/09/19 17:49:55 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit(int error) //o error guardado en estructura
{
	//manejar errores especificos de exit
	if (ft_isdigit(error) != 1)
		error = 2;

	if (error != 0)
		ft_write_error(error);
	exit(error);
}
