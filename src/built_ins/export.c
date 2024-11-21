/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:31:26 by aarenas-          #+#    #+#             */
/*   Updated: 2024/11/21 18:02:21 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_free_search(char *name, char *value)
{
	if (name)
		free(name);
	if (value)
		free(value);
}

static int	ft_search(t_env **lst, char *str)
{
	t_env	*node;
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
	node = *lst;
	while (node)
	{
		if (ft_strncmp(node->name, name, ft_strlen(node->name)) == 0)
		{
			free(node->value);
			node->value = NULL;
			node->value = value;
			return (free(name), 0);
		}
		node = node->next;
	}
	return (ft_free_search(name, value), 1);
}

t_env	*ft_add_to_env(char *str, t_env *lst)
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
		lst = ft_lstnew_tenv(name, value);
	else
	{
		ft_lstadd_back_tenv(&lst, ft_lstnew_tenv(name, value));
	}
	return (lst);
}

void	ft_export(char *str, t_data *data)
{
	t_env	*aux;

	if (str && ft_isdigit(str[0]) == 1)
		return (printf("minishell: export: `%s`: not a valid identifier\n",
				str), data->error = 1, (void)0);
	if (str && ft_isdigit(str[0]) == 0 && ft_search(&data->env, str) == 1)
		data->env = ft_add_to_env(str, data->env);
	if (str && ft_isdigit(str[0]) == 0
		&& ft_search(&data->env_export, str) == 1)
		data->env_export = ft_add_to_env(str, data->env_export);
	if (!str)
		data->env_export = ft_sort(data->env_export);
	if (!str)
		aux = data->env_export;
	while (!str && aux)
	{
		printf("declare -x %s", aux->name);
		if (aux->value)
			printf("=\"%s\"", aux->value);
		printf("\n");
		aux = aux->next;
	}
	data->error = 0;
}
