/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:35:32 by jcallejo          #+#    #+#             */
/*   Updated: 2024/09/24 12:56:47 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_input_classifier(t_data *data)
{
	t_input	*aux;

	aux = data->list;
	while (aux)
	{
		if (aux->input[0] == '\'' && ft_strlen(aux->input) > 1
			&& aux->content[ft_strlen(aux->content) - 1] == '\'')
			aux->type = SINGLE_QUOTE;
		else if (aux->input[0] == '\"' && ft_strlen(aux->input) > 1
			&& aux->content[ft_strlen(aux->content) - 1] == '\"')
			aux->type = DOUBLE_QUOTE;
		else if (aux->content[0] == '<' && aux->content[1] == '<')
			aux->type = HEREDOC;
		else if (aux->content[0] == '>' && aux->content[1] == '>')
			aux->type = OUTPUT_APPEND;
		else if (aux->content[0] == '<')
			aux->type = INPUT_REDIRECT;
		else if (aux->content[0] == '>')
			aux->type = OUTPUT_REDIRECT;
		else if (aux->content[0] == '|')
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
