/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:10:33 by aarenas-          #+#    #+#             */
/*   Updated: 2024/10/17 10:24:03 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_delete_node(t_env *prev_node)
{
	t_env	*node_to_delete;

	node_to_delete = prev_node->next;
	if (node_to_delete->next)
		prev_node->next = node_to_delete->next;
	else
		prev_node->next = NULL;
	if (node_to_delete->name)
		free(node_to_delete->name);
	if (node_to_delete->value)
		free(node_to_delete->value);
	node_to_delete->name = NULL;
	node_to_delete->value = NULL;
	if (node_to_delete)
		free(node_to_delete);
	node_to_delete = NULL;
}

void	ft_unset(t_arg_list *data, char *name)
{
	t_env	*export_node;
	t_env	*env_node;

	env_node = data->env;
	while (env_node->next)
	{
		if (ft_strncmp(env_node->next->name, name, ft_strlen(name)) == 0)
		{
			ft_delete_node(env_node);
			break ;
		}
		env_node = env_node->next;
	}
	export_node = data->env_export;
	while (export_node->next)
	{
		if (ft_strncmp(export_node->next->name, name, ft_strlen(name)) == 0)
		{
			ft_delete_node(export_node);
			break ;
		}
		export_node = export_node->next;
	}
}
