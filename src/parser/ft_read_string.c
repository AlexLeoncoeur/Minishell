/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:08:04 by jcallejo          #+#    #+#             */
/*   Updated: 2024/09/24 12:34:08 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_new_token(t_data *data, int start, int end)
{
	t_input	*new;
	t_input	*aux;
	char	*str;

	str = ft_substr(data->line, s, e - s);
	new = malloc(sizeof(t_input));
	if (!new)
		return (NULL);
	new->input = str;
	new->type = 0;
	new->next = NULL;
	if (!data->list)
		data->list = new;
	else
	{
		aux = data->list;
		while (aux->next)
			aux = aux->next;
		new->previous = tmp;
		aux->next = new;
	}
}

static void	ft_redir_pipe_token(t_data *data, int *start, int *count, char div)
{
	int	s;
	int	c;

	s = *start;
	c = *count;
	c++;
	if (data->line[c] == div && div != '|')
		c++;
	if (div == '<' || div == '>')
	{
		while (data->line[c] == ' ')
			c++;
		while (data->line[c] && ft_strchr("|<>", data->line[c]) == 0)
			c++;
	}
	ft_new_token(data, s, c);
	*count = c;
}

static void	ft_quote_token(t_data *data, int *start, int *counter, char quote)
{
	int	s;
	int	c;

	s = *start;
	c = *counter;
	while (data->line[c] && data->line[c] != quote)
		c++;
	if (data->line[c] == quote)
		c++;
	ft_new_token(data, s, c);
	*counter = c;
}

static void	ft_normal_token(t_data *data, int *start, int *counter)
{
	int	s;
	int	c;

	c = *counter;
	s = *start;
	while (data->line[c] && data->line[c] == ' ')
		c++;
	s = c;
	while (data->line[c] && data->line[c] != '\'' && data->line[c] != '\"'
		&& ft_strchr("|<>", data->line[c]) == 0)
		c++;
	if (c > s)
		ft_new_token(data, s, c);
	*counter = c;
}

void	ft_read_string(t_data *data)
{
	int	counter;
	int	start;

	c = 0;
	while (data.line[counter])
	{
		start = counter;
		if (data->line[counter] == '\'')
			ft_quote_token(data, &start, &counter, '\'');
		else if (data->line[counter] == '\"')
			ft_quote_token(data, &start, &counter, '\"');
		else if (ft_strchr("|<>", data->line[c]))
			ft_redir_pipe_token(data, &start, &counter, data->line[counter]);
		else
			ft_normal_token([data, &start, &counter]);
	}
}
