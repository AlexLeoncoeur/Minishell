/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:08:04 by jcallejo          #+#    #+#             */
/*   Updated: 2024/10/29 12:15:33 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	ft_join_and_free(char *s1, char *s2)
{
	char	tmp;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	return (tmp);
}

static int	ft_check_env(t_data *data, char **home, char **pwd)
{
	if (!ft_get_env(data, "HOME" || !ft_get_env(data, "PWD")))
		return (0);
	*home = ft_get_env(data, "HOME")->value;
	*pwd = ft_get_env(data, "PWD")->value;
	if (!ft_get_env(data, "USER"))
		return (0);
	return (1);
}

static char	*get_string(t_data *data)
{
	char	*string;
	char	*aux;
	char	**home;
	char	**pwd;

	if (!ft_check_env(data, &home, &pwd))
		return ("minishell$ ");
	aux = ft_get_env(data, "USER")->value;
	string = ft_join_and_free(aux, ":");
	if (ft_strncmp(home, pwd, ft_strlen(home)) == 0)
		aux = ft_join_and_free(aux, "~");
	else
	{
		string = ft_join_and_free(aux, pwd);
		aux = ft_join_and_free(string, "$ ");
		return (aux);
	}
	if (ft_strcmp(home, pwd))
		return (ft_join_and_free(aux, "$ "));
	else
	{
		string = ft_join_and_free(aux, pwd + ft_strlen(home));
		return (ft_join_and_free(string, "$ "));
	}
}

int	ft_read_string(t_data *data)
{
	char	*string;
	char	*aux;

	string = get_string(data);
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	aux = readline(string);
	if (!aux)
	{
		printf("\n");
		ft_exit(NULL, data);
		return (free(string), free(aux), 0);
	}
	data->input = ft_strtrim(aux, " \t");
	free(aux);
	if (!data->input)
		return (0);
	else if (*(data->input))
		add_history(data->input);
	free(string);
	return (1);
}