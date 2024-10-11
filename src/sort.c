/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:51:01 by aarenas-          #+#    #+#             */
/*   Updated: 2024/10/11 11:49:43 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_tenv_lstsize(t_env *lst)
{
	t_env	*aux;
	int		i;

	aux = lst;
	i = 0;
	while (aux)
	{
		i++;
		aux = aux->next;
	}
	return (i);
}

static void	ft_swap(t_env **lst)
{
	t_env	*aux;
	t_env	*aux2 = *lst;

	for (int i = 0; i < ft_tenv_lstsize(*lst); i++)
	{
		printf("i: %d\n", i);
		printf("	%s=%s\n", aux2->name, aux2->value);
		printf("\n");
		aux2 = aux2->next;
	}

	if (!lst || ft_tenv_lstsize(*lst) < 2)
		return ;
	aux = (*lst)->next;
	(*lst)->next = aux->next;
	aux->next = (*lst);
	(*lst) = aux;
	aux = NULL;
}

static int	ft_check_sort(t_env *lst)
{
	t_env	*aux;

	aux = lst;
	while (aux->next)
	{
		if (ft_strncmp(aux->name, aux->next->name, 1) > 0)
			ft_swap(&aux);
		return (1);
	}
	return (0);
}

t_env	*ft_sort(t_env *lst)
{
	t_env	*aux;

	while (ft_check_sort(lst))
	{
		aux = lst;
		while (aux->next)
		{
			if (aux->next && ft_strncmp(aux->name, aux->next->name, 1) > 0)
			{
				printf("Ola k ase, segfault o k ase\n");
				if (aux == lst)
					lst = aux->next;
				ft_swap(&aux);
			}
			aux = aux->next;
		}
	}
	return (aux);
}
