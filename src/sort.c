/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:51:01 by aarenas-          #+#    #+#             */
/*   Updated: 2024/10/14 14:05:52 by aarenas-         ###   ########.fr       */
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

	if (!lst || ft_tenv_lstsize(*lst) < 1)
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
			return (1);
		aux = aux->next;
	}
	return (0);
}

t_env	*ft_sort(t_env *lst)
{
	t_env	*aux;
	t_env	*aux_prev_node;
	int		i;

	while (ft_check_sort(lst))
	{
		i = 0;
		aux = lst;
		aux_prev_node = lst;
		while (aux)
		{
			if (aux->next && ft_strncmp(aux->name, aux->next->name, 1) > 0)
			{
				if (aux_prev_node != lst)
					aux_prev_node->next = aux->next;
				if (aux == lst)
					lst = lst->next;
				ft_swap(&aux);
			}
			aux = aux->next;
			if (aux_prev_node->next != aux)
				aux_prev_node = aux_prev_node->next;
		}
	}
	return (lst);
}

/* t_env	*aux2 = lst;

for (int i = 0; i < ft_tenv_lstsize(lst); i++)
{
	printf("i: %d: %s=%s\n", i, aux2->name, aux2->value);
	printf("\n");
	if (aux2->next)
		aux2 = aux2->next;
} */