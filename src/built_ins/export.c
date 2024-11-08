/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:31:26 by aarenas-          #+#    #+#             */
/*   Updated: 2024/11/08 11:59:57 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	{
		printf("Minishell: export: `%s`: not a valid identifier\n", str);
		return ;
	}
	if (str && ft_isdigit(str[0]) == 0)
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
		printf("declare -x ");
		printf("%s", aux->name);
		if (aux->value)
			printf("=\"%s\"", aux->value);
		printf("\n");
		aux = aux->next;
	}
}
