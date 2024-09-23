/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:01:59 by aarenas-          #+#    #+#             */
/*   Updated: 2024/09/23 17:24:52 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		perror("Error: ");
	printf("%d", errno);
	ft_putstr(path);
	free(path);
}
//anadir data como parametro y setear data->error a 0 si todo salio bien
//si algo sale mal, igualar el error a errno