/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:06:10 by aarenas-          #+#    #+#             */
/*   Updated: 2024/04/16 19:21:53 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*aux;

	if (lst == NULL)
		return (NULL);
	aux = lst;
	while (aux->next != NULL)
		aux = aux->next;
	return (aux);
}

/* int	main(void)
{
	t_list	*lst;
	t_list	*aux;

	lst = NULL;
	aux = ft_lstlast(lst);
} */
