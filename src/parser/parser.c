/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:35:32 by jcallejo          #+#    #+#             */
/*   Updated: 2024/09/26 23:19:37 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_dequote(t_input *input)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 1;
	str = malloc(sizeof(char *) * ft_strlen(input->input));
	if (!str)
		return ;
	while (input)
	{
		str[i] = input->input[j];
		i++;
		j++;
	}
	str[i - 1] = 0;
	free (input->input);
	input->input = str;
}

static	void	ft_value_replace(t_input *input, t_data *data)
{
	int		i;
	int		j;
	char	*var;
	char	*val;

	i = 0;
	j = 0;
	while (input->input[i] && input->input[i] != '$')
		i++;
	if (input->input[i] == '$')
	{
		i++;
		j = i;
		while (input->input[i]
			&& ft_strchr("'\"<>| $", input->input[i] == NULL))
			i++;
		var = ft_substr(input->input, j, i - j);
		if (ft_strcmp(var, "?") == 0)
			val = ft_itoa(data->status);
		else
			val = ft_get_env(var, data);
		ft_replace_aux(input, j - 1, j + ft_strlen(var), val);
		free(var);
		free(val);
	}
}

static void	ft_input_classifier(t_data *data)
{
	t_input	*aux;

	aux = data->list;
	while (aux)
	{
		if (aux->type == 1 || aux->type == 2)
			ft_dequote(aux);
		if (aux->type == 0 || aux->type == 2 && ft_strchr(aux->input, '$'))
			ft_value_replace(aux, data);
	}
}

static void	ft_input_classifier(t_data *data)
{
	t_input	*aux;

	aux = data->list;
	while (aux)
	{
		if (aux->input[0] == '\'' && ft_strlen(aux->input) > 1
			&& aux->input[ft_strlen(aux->input) - 1] == '\'')
			aux->type = SINGLE_QUOTE;
		else if (aux->input[0] == '\"' && ft_strlen(aux->input) > 1
			&& aux->input[ft_strlen(aux->input) - 1] == '\"')
			aux->type = DOUBLE_QUOTE;
		else if (aux->input[0] == '<' && aux->input[1] == '<')
			aux->type = HEREDOC;
		else if (aux->input[0] == '>' && aux->input[1] == '>')
			aux->type = OUTPUT_APPEND;
		else if (aux->input[0] == '<')
			aux->type = INPUT_REDIRECT;
		else if (aux->input[0] == '>')
			aux->type = OUTPUT_REDIRECT;
		else if (aux->input[0] == '|')
			aux->type = PIPE;
		else
			aux->type = NORMAL_INPUT;
		aux = aux->next;
	}
}

void	ft_parser(t_data *data)
{
	ft_read_string(data);
	ft_input_classifier(data);
}
