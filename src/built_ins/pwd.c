/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:01:59 by aarenas-          #+#    #+#             */
/*   Updated: 2024/10/19 17:14:24 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(t_data *data)
{
	char	*path;

	if (data)
		data = NULL;
	path = getcwd(NULL, 0);
	if (!path)
		perror("Error: ");
	//data->error = 0; //errno
	path = ft_strjoin(path, "\n");
	ft_putstr(path);
	free(path);
}
//anadir data como parametro y setear data->error a 0 si todo salio bien
//si algo sale mal, igualar el error a errno