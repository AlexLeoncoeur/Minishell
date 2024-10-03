/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:07:09 by aarenas-          #+#    #+#             */
/*   Updated: 2024/10/03 13:35:50 by aarenas-         ###   ########.fr       */
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

t_env	*ft_lstnew_tenv(char *name, char *value)
{
	t_env	*newlist;

	newlist = malloc(sizeof(t_env));
	if (newlist == NULL)
		return (NULL);
	newlist->name = name;
	newlist->value = value;
	newlist->next = NULL;
	return (newlist);
}

t_env	*ft_lst_env(char **envp)
{
	t_env	*env;
	char	*name;
	char	*value;
	char	*cut;
	int		i;

	i = 0;
	if (!envp)
		return (NULL);
	env = NULL;
	while (envp[i])
	{
		cut = ft_strchr(envp[i], '=');
		name = ft_substr(envp[i], 0, (ft_strlen(envp[i]) - ft_strlen(cut)));
		value = ft_substr(envp[i], ((ft_strlen(envp[i]) - ft_strlen(cut)) + 1),
				ft_strlen(cut) - 1);
		if (!env)
			env = ft_lstnew_tenv(name, value);
		else
			ft_lstadd_back_tenv(&env, ft_lstnew_tenv(name, value));
		i++;
	}
	return (env);
}
//strchr('=') y usar esa pos, coger todo lo que hay antes para name
//	y todo lo que ahy despues para value