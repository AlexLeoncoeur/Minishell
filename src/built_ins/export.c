/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:31:26 by aarenas-          #+#    #+#             */
/*   Updated: 2024/10/15 15:56:47 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_add_to_env(char *str, t_arg_list *data, int i)
{
	char	*name;
	char	*value;
	char	*cut;

	cut = ft_strchr(str, '=');
	name = ft_substr(str, 0, (ft_strlen(str) - ft_strlen(cut)));
	value = NULL;
	if (cut)
		value = ft_substr(str, ((ft_strlen(str) - ft_strlen(cut)) + 1),
				ft_strlen(cut) - 1);
	if (!data->env)
	{
		data->env = ft_lstnew_tenv(name, value, i);
		data->env_export = ft_lstnew_tenv(name, value, i);
	}
	else
	{
		ft_lstadd_back_tenv(&data->env, ft_lstnew_tenv(name, value, i));
		ft_lstadd_back_tenv(&data->env_export, ft_lstnew_tenv(name, value, i));
	}
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
		ft_add_to_env(str, data, -1);
	if (!str)
	{
		aux = ft_sort(data->env_export);
	}
	int i = 0;
	while (!str && aux)
	{
		printf("%d: ", i);
		printf("declare -x ");
		printf("%s", aux->name);
		if (aux->value)
			printf("=\"%s\"", aux->value);
		printf("\n");
		aux = aux->next;
		i++;
	}
	// ft_env(data->env);
}

//Necesito guardar los env como estatico para que se mantenga durante
//	multiples ejecuciones?	
//Escribe todas las variables incluso sin valor
//Escribir los env con "declare -x " delante y por orden alfabético