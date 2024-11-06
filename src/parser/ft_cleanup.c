/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:04:12 by jcallejo          #+#    #+#             */
/*   Updated: 2024/11/06 10:55:43 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_clean_cmd(t_data *data)
{
	t_cmd	*aux;
	t_redir	*raux;

	while (data->cmd)
	{
		aux = data->cmd;
		data->cmd = data->cmd->next;
		free(aux->path);
		ft_clean_array(aux->argv);
		while (aux->redir)
		{
			raux = aux->redir;
			aux->redir = aux->redir->next;
			free(raux->file);
			free(raux);
		}
		free(aux);
	}
}

void	ft_clean_array(char **array)
{
	char	*aux;

	if (array == NULL)
		return ;
	aux = array;
	while (*aux)
	{
		free(aux);
		aux++;
	}
	free(array);
}
