/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:07:09 by aarenas-          #+#    #+#             */
/*   Updated: 2024/10/15 15:54:36 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*ft_lstlast_tenv(t_env *lst)
{
	t_env	*aux;

	if (lst == NULL)
		return (NULL);
	aux = lst;
	while (aux->next)
		aux = aux->next;
	return (aux);
}

void	ft_lstadd_back_tenv(t_env **lst, t_env	*new)
{
	t_env	*aux;

	if (*lst == NULL)
		*lst = new;
	else
	{
		aux = ft_lstlast_tenv(*lst);
		aux->next = new;
	}
}

t_env	*ft_lstnew_tenv(char *name, char *value, int i)
{
	t_env	*newlist;

	newlist = malloc(sizeof(t_env));
	if (newlist == NULL)
		return (NULL);
	newlist->name = name;
	newlist->value = value;
	newlist->pos = i;
	newlist->next = NULL;
	return (newlist);
}

void	ft_lst_env(t_arg_list *data)
{
	int		i;

	i = 0;
	if (!data->envp)
		return ;
	while (data->envp[i])
	{
		ft_add_to_env(data->envp[i], data, i);
		i++;
	}
}
//strchr('=') y usar esa pos, coger todo lo que hay antes para name
//	y todo lo que ahy despues para value