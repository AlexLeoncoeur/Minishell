/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:00:08 by aarenas-          #+#    #+#             */
/*   Updated: 2024/11/22 17:03:05 by aarenas-         ###   ########.fr       */
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

static void	ft_manage_pwd_change(t_data *data, char *oldpwd_env)
{
	char	*pwd_env;
	char	*pwd_export;
	char	*oldpwd_export;

	oldpwd_export = getcwd(NULL, 0);
	pwd_env = getcwd(NULL, 0);
	pwd_export = getcwd(NULL, 0);
	ft_change_pwd_env(&data->env, "PWD", pwd_env);
	ft_change_pwd_env(&data->env_export, "PWD", pwd_export);
	ft_change_pwd_env(&data->env, "OLDPWD", oldpwd_env);
	ft_change_pwd_env(&data->env_export, "OLDPWD", oldpwd_export);
}

void	ft_cd(t_data *data, char **str)
{
	char	*home;
	char	*oldpwd_env;

	home = getenv("HOME");
	if (str && str[1])
	{
		data->error = 1;
		return (printf("minishell: cd: too many arguments\n"), (void)0);
	}
	if (str && ft_strncmp(str[0], "-", 1) == 0
		&& chdir(ft_search(&data->env, "OLDPWD=")) < 0)
		perror("minishell: cd");
	oldpwd_env = getcwd(NULL, 0);
	if (str && ft_strncmp(str[0], "-", 1) != 0 && chdir(str[0]) < 0)
		perror("minishell: cd");
	if (!str && chdir(home) < 0)
		perror("minishell: cd");
	ft_manage_pwd_change(data, oldpwd_env);
	data->error = 0;
}
