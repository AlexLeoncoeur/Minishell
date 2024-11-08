/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:31:26 by aarenas-          #+#    #+#             */
/*   Updated: 2024/11/08 13:23:31 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_search(t_env **lst, char *str)
{
	t_env	*node;
	int		i;
	char	*name;
	char	*value;
	char	*cut;

	name = NULL;
	cut = ft_strchr(str, '=');
	name = ft_substr(str, 0, (ft_strlen(str) - ft_strlen(cut)));
	value = NULL;
	if (cut)
		value = ft_substr(str, ((ft_strlen(str) - ft_strlen(cut)) + 1),
				ft_strlen(cut) - 1);
	i = 0;
	node = *lst;
	while (node->next)
	{
		if (i == 0 && ft_strncmp(node->name, name, ft_strlen(node->name)) == 0)
		{
			node->value = value;
			return (0);
		}
		node = node->next;
	}
	return (1);
}

t_env	*ft_add_to_env(char *str, t_env *lst, int i)
{
	char	*name;
	char	*value;
	char	*cut;

	name = NULL;
	cut = ft_strchr(str, '=');
	name = ft_substr(str, 0, (ft_strlen(str) - ft_strlen(cut)));
	value = NULL;
	if (cut)
		value = ft_substr(str, ((ft_strlen(str) - ft_strlen(cut)) + 1),
				ft_strlen(cut) - 1);
	if (!lst)
		lst = ft_lstnew_tenv(name, value, i);
	else
	{
		ft_lstadd_back_tenv(&lst, ft_lstnew_tenv(name, value, i));
	}
	return (lst);
}

void	ft_export(char *str, t_cmd *cmd)
{
	t_env	*aux;

	if (str && ft_isdigit(str[0]) == 1)
		return (printf("minishell: export: `%s`: not a valid identifier\n",
				str), (void)0);
	if (str && ft_isdigit(str[0]) == 0 && ft_search(cmd, str) == 0)
	{
		cmd->data->env = ft_add_to_env(str, cmd->data->env, -1);
		cmd->data->env_export = ft_add_to_env(str, cmd->data->env_export, -1);
	}
	if (!str)
		cmd->data->env_export = ft_sort(cmd->data->env_export);
	if (!str)
		aux = cmd->data->env_export;
	while (!str && aux)
	{
		printf("declare -x %s", aux->name);
		if (aux->value)
			printf("=\"%s\"", aux->value);
		printf("\n");
		aux = aux->next;
	}
}
