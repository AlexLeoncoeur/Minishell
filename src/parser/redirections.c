/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:36:51 by jcallejo          #+#    #+#             */
/*   Updated: 2024/10/02 11:45:44 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_redirections(t_data *data, int *infd, int *outfd)
{
	t_input	*aux;

	aux = data->list;
	while (aux->previous && aux->type != PIPE)
		aux = aux->previous;
	while (aux)
	{
		if (aux->type == HEREDOC)
			ft_heredoc(aux, infd, data);
		else if (aux->type == OUTPUT_APPEND)
			ft_in_redir(aux, infd);
		else if (aux->type == INPUT_REDIRECT)
			ft_out_redir(aux, outfd, 1, data);
		else if (aux->type == OUTPUT_REDIRECT)
			ft_out_redir(aux, outfd, 0, data);
	}
}
