/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:00:08 by aarenas-          #+#    #+#             */
/*   Updated: 2024/10/30 09:46:19 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_change_pwd_env(t_env **lst, char *name, char *new_route)
{
	t_env	*aux;
	int		i;

	i = 0;
	aux = *lst;
	while (aux->next)
	{
		if (i == 0 && ft_strncmp(aux->name, name, ft_strlen(aux->name)) == 0)
		{
			if (aux->value)
				free(aux->value);
			aux->value = new_route;
			break ;
		}
		aux = aux->next;
	}
}

void	ft_cd(t_arg_list *data, char *str)
{
	char	*pwd_env;
	char	*pwd_export;
	char	*oldpwd_env;
	char	*oldpwd_export;

	oldpwd_env = getcwd(NULL, 0);
	oldpwd_export = getcwd(NULL, 0);
	if (chdir(str) < 0)
		perror("minishell: cd");
	pwd_env = getcwd(NULL, 0);
	pwd_export = getcwd(NULL, 0);
	ft_change_pwd_env(&data->env, "PWD", pwd_env);
	ft_change_pwd_env(&data->env_export, "PWD", pwd_export);
	ft_change_pwd_env(&data->env, "OLDPWD", oldpwd_env);
	ft_change_pwd_env(&data->env_export, "OLDPWD", oldpwd_export);
}