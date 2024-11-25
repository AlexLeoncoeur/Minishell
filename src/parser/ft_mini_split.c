/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 02:16:15 by jcallejo          #+#    #+#             */
/*   Updated: 2024/11/22 13:34:34 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_args(char *str)
{
	int		i;
	int		args;
	char	quote;

	i = 0;
	args = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '"'))
			quote = str[i];
		else if (quote == str[i])
			quote = 0;
		if (str[i] != ' ' && str[i + 1] != '\''
			&& str[i + 1] != '"' && !quote)
		{
			while (str[i] && str[i] != ' ' && str[i] != quote)
				i++;
			args++;
		}
		else
			i++;
	}
	return (args);
}

static int	get_next_cut(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '"'))
			quote = str[i];
		else if (quote == str[i] && str[i + 1] && str[i + 1] == ' ')
			return (i);
		else if (quote == str[i])
			quote = 0;
		if (str[i] != ' ' && !quote)
		{
			while (str[i] && str[i] != ' ' && str[i] != quote)
				i++;
			return (i);
		}
		else
			i++;
	}
	return (i);
}

char	**ft_minisplit(char *str)
{
	char	**res;
	char	*aux;
	int		i;
	int		args;

	args = count_args(str);
	if (!args)
		return (NULL);
	res = malloc(sizeof(char *) * args + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (*str)
	{
		aux = ft_substr(str, 0, get_next_cut(str) + 1);
		res[i++] = ft_strtrim(aux, " ");
		free(aux);
		if (!str[get_next_cut(str)])
			break ;
		str = &str[get_next_cut(str) + 1];
	}
	res[args] = 0;
	return (res);
}
