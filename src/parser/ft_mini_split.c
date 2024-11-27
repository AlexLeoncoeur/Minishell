/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 02:16:15 by jcallejo          #+#    #+#             */
/*   Updated: 2024/11/27 13:57:49 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_args_if(char *str, int *i, int args, char *quote)
{
	while (str[*i] && str[*i] != ' ')
	{
		if (str[*i] && (str[*i] == '\'' || str[*i] == '"') && !*quote)
		{
			*quote = str[*i];
			*i += 1;
		}
		else if (str[*i] == *quote)
			*quote = 0;
		if (!ft_strncmp(&str[*i], "<<", 2)
			|| !ft_strncmp(&str[*i], ">>", 2))
		{
			*i += 2;
			break ;
		}
		else if (!ft_strncmp(&str[*i], "<", 1)
			|| !ft_strncmp(&str[*i], ">", 1))
		{
			*i += 1;
			break ;
		}
		*i += 1;
	}
	args++;
	return (args);
}

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
		if (str[i] != ' ' && !quote && str[i] != '\'' && str[i] != '"')
			args = count_args_if(str, &i, args, &quote);
		else
			i++;
	}
	return (args);
}

static void	aux_next_cut(char *str, int *i, char *quote)
{
	while (str[*i])
	{
		if (str[*i] && (str[*i] == '\'' || str[*i] == '"'))
			*quote = str[*i];
		else if (*quote == str[*i])
			*quote = 0;
		if (!ft_strncmp(&str[*i], "<<", 2) || !ft_strncmp(&str[*i], ">>", 2))
		{
			*i += 1;
			break ;
		}
		else if (!ft_strncmp(&str[*i], "<", 1) || !ft_strncmp(&str[*i], ">", 1))
			break ;
		else if (!*quote && str[*i] == ' ')
			break ;
		*i += 1;
	}
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
		if (str[i] != ' ' && !quote && str[i] != '\'' && str[i] != '"')
		{
			aux_next_cut(str, &i, &quote);
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
		res[i++] = ft_custom_strtrim(aux, " ");
		free(aux);
		if (!str[get_next_cut(str)])
			break ;
		str = &str[get_next_cut(str) + 1];
	}
	res[args] = 0;
	return (res);
}
