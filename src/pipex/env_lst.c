/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:07:09 by aarenas-          #+#    #+#             */
/*   Updated: 2024/09/25 18:48:28 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_lstadd_back_tenv(t_env **lst, t_env	*new)
{
	t_env	*aux;

	if (*lst == NULL)
		*lst = new;
	else
	{
		aux = ft_lstlast(*lst);
		aux->next = new;
	}
}

static t_env	*ft_lstnew_tenv(char *name, char *value)
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

	if (!envp)
		return (NULL);
	while (envp[i])
	{
		cut = ft_strchr(envp[i], '=');
		name = ft_substr(envp[i], 0, (ft_strlen(envp[i]) - ft_strlen(&cut)));
		value = ft_substr(envp[i], cut, ft_strlen(&cut));
		if (!env)
			env = ft_lstnew_tenv(name, value);
		else
			ft_lstadd_back_tenv(&env, ft_lstnew_tenv(name, value));
		free(cut);
		free(name);
		free(value);
		i++;
	}
}
//strchr('=') y usar esa pos, coger todo lo que hay antes para name
//	y todo lo que ahy despues para value