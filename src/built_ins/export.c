/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:31:26 by aarenas-          #+#    #+#             */
/*   Updated: 2024/10/03 14:15:03 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_export(char *str, t_env *env)
{
	t_env	*aux;

	ft_lstadd_back_tenv(&env, ft_lstnew_tenv(str, NULL));
	if (!str)
		aux = env;
	while (!str && aux)
	{
		printf("%s", aux->name);
		if (aux->value)
			printf("=%s", aux->value);
		printf("\n");
		aux = aux->next;
	}
}

//Necesito guardar los env como estatico para que se mantenga durante
//	multiples ejecuciones?	
//Escribe todas las variables incluso sin valor