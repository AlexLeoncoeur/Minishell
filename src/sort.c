/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:51:01 by aarenas-          #+#    #+#             */
/*   Updated: 2024/10/10 14:46:10 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_swap(t_env **lst)
{
	t_env	*aux;

	if (!lst || ft_pushswap_lstsize(*lst) < 2)
		return ;
	aux = (*lst)->next;
	(*lst)->next = aux->next;
	aux->next = (*lst);
	(*lst) = aux;
	aux = NULL;
	ft_check_stack(*lst);
}

t_env	ft_sort(t_env *lst)
{
	t_env	*aux;
	int		i;

	aux = lst;
	i = 0;
	while (aux)
	{
		if (ft_strncmp(aux->name, aux->next->name, 1) < 0)
			ft_swap(&aux);
		aux = aux->next;
	}
}
