/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:01:59 by aarenas-          #+#    #+#             */
/*   Updated: 2024/10/19 14:22:57 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(t_data *data)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		perror("Error: ");
	data->error = errno;
	ft_putstr(path);
	free(path);
}
//anadir data como parametro y setear data->error a 0 si todo salio bien
//si algo sale mal, igualar el error a errno