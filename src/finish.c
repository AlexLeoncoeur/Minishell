/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:28:18 by aarenas-          #+#    #+#             */
/*   Updated: 2024/10/19 14:11:20 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_free_tenv(t_env **lst)
{
	t_env	*aux;

	if (!lst)
		return ;
	while (*lst)
	{
		if ((*lst)->name)
			free((*lst)->name);
		if ((*lst)->value)
			free((*lst)->value);
		(*lst)->name = NULL;
		(*lst)->value = NULL;
		aux = *lst;
		*lst = aux->next;
		free(aux);
	}
}

void	ft_free_data(t_arg_list *data)
{
	ft_free_tenv(&data->env);
	ft_free_tenv(&data->env_export);
}
