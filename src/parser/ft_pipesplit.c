/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipesplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:39:43 by jcallejo          #+#    #+#             */
/*   Updated: 2024/11/06 10:57:47 by jcallejo         ###   ########.fr       */
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
			quote = str[i++];
		while (str[i] && quote && str[i] != quote && str[i + 1])
			i++;
		if (quote == str[i])
			quote = 0;
		if (str[i] == '|')
			args++;
		if (str[i])
			i++;
	}
	return (args + 1);
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
			quote = str[i++];
		while (str[i] && quote && str[i] != quote && str[i + 1])
			i++;
		if (quote == str[i])
			quote = 0;
		if (str[i] == '|')
			return (i);
		if (str[i])
			i++;
	}
	return (i);
}

char	**ft_pipesplit(char *str)
{
	char	**result;
	int		i;
	int		args;

	args = count_args(str);
	result = malloc(sizeof(char *) * (args + 1));
	if (!result)
		return (NULL);
	result[args] = 0;
	i = 0;
	while (*str)
	{
		result[i] = ft_substr(str, 0, get_next_cut(str));
		if (!str[get_next_cut(str)])
			break ;
		str = &str[get_next_cut(str) + 1];
		i++;
	}
	return (result);
}
