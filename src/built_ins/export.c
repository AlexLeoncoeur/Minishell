/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:31:26 by aarenas-          #+#    #+#             */
/*   Updated: 2024/10/17 12:54:17 by aarenas-         ###   ########.fr       */
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

void	ft_export(char *str, t_arg_list *data)
{
	t_env	*aux;

	if (str && ft_isdigit(str[0]) == 1)
	{
		printf("Minishell: export: `%s`: not a valid identifier\n", str);
		return ;
	}
	if (str && ft_isdigit(str[0]) == 0)
	{
		ft_add_to_env(str, data->env, -1);
		ft_add_to_env(str, data->env_export, -1);
	}
	if (!str)
	{
		aux = ft_sort(data->env_export);
	}
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

//Necesito guardar los env como estatico para que se mantenga durante
//	multiples ejecuciones?	
//Escribe todas las variables incluso sin valor
//Escribir los env con "declare -x " delante y por orden alfabético