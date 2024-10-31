/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:04:12 by jcallejo          #+#    #+#             */
/*   Updated: 2024/10/01 11:07:37 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_clean_array(char **array)
{
	char	*aux;

	if (array == NULL)
		return ;
	aux = array;
	while (*aux)
	{
		free(aux);
		aux++;
	}
	free(array);
} //¿hace falta realmente esto ahora que estoy cambiando? quien sabe
