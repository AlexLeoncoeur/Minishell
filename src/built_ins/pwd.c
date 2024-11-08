/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:01:59 by aarenas-          #+#    #+#             */
/*   Updated: 2024/11/08 12:00:18 by jcallejo         ###   ########.fr       */
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
		perror("Error");
	//data->error = 0; //errno
	path = ft_strjoin(path, "\n");
	ft_putstr(path);
	free(path);
}
