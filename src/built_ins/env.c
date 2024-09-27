/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:36:20 by aarenas-          #+#    #+#             */
/*   Updated: 2024/09/27 14:47:28 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(t_env *env)
{
	t_env	*aux;

	while (aux)
	{
		printf("%s=%s\n", aux->name, aux->value);
		aux = aux->next;
	}
}
