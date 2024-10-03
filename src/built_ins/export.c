/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:31:26 by aarenas-          #+#    #+#             */
/*   Updated: 2024/10/03 19:33:36 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_add_to_env(char *str, t_arg_list *data)
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
		data->env = ft_lstnew_tenv(name, value);
	else
		ft_lstadd_back_tenv(&data->env, ft_lstnew_tenv(name, value));
}

void	ft_export(char *str, t_arg_list *data)
{
	t_env	*aux;

	if (str)
		printf("%s", str);
	ft_add_to_env(str, data);
	if (!str)
		aux = data->env;
	while (!str && aux)
	{
		printf("%s", aux->name);
		if (aux->value)
			printf("=%s", aux->value);
		printf("\n");
		aux = aux->next;
	}
	ft_env(data->env);
}

//Necesito guardar los env como estatico para que se mantenga durante
//	multiples ejecuciones?	
//Escribe todas las variables incluso sin valor
//Escribir los env con "declare -x " delante y por orden alfabético