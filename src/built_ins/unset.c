/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:10:33 by aarenas-          #+#    #+#             */
/*   Updated: 2024/10/16 13:00:03 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_delete_node(t_env *prev_node)
{
	t_env	*node_to_delete;

	node_to_delete = prev_node->next;
	prev_node->next = node_to_delete->next;
	if (node_to_delete->name)
		free(node_to_delete->name);
	if (node_to_delete->value)
		free(node_to_delete->value);
	if (node_to_delete)
		free(node_to_delete);
}

void	ft_unset(t_env *lst, char *name)
{
	t_env	*aux;

	aux = lst;
	while (aux->next)
	{
		if (ft_strncmp(aux->next->name, name, ft_strlen(name)))
		{
			ft_delete_node(aux);
			break ;
		}
		aux = aux->next;
	}
}
