/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:36:51 by jcallejo          #+#    #+#             */
/*   Updated: 2024/10/09 11:04:53 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_out_redir(t_input *current, int	*outfd, int append,
	t_data *data)
{
	int		fd;
	char	**aux;

	aux = ft_split(current->input, ' ');
	if (!aux[1] || aux == NULL)
	{
		ft_clean_array(aux);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("syntax error near unexpected token 'newline'\n", 2);
		data->redir_err = 1;
		return ;
	}
	if (append == 1)
		fd = open(aux[1], O_WRONLY | O_CREAT | O_APPEND);
	else
		fd = open(aux[1], O_WRONLY | O_CREAT | O_TRUNC);
	ft_clean_array(aux);
	if (*outfd != 1)
		close(*outfd);
	*outfd = fd;
}

static void	ft_in_redir(t_input *current, int *infd)
{
	int		fd;
	char	**aux;

	aux = ft_split(current->input, ' ');
	if (!aux[1] || aux == NULL)
	{
		ft_clean_array(aux);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("syntax error near unexpected token 'newline'\n", 2);
	}
	fd = open(aux[1], O_RDONLY);
	ft_clean_array(aux);
	if (fd == -1)
	{
		perror("open: ");
		return ;
	}
	if (*infd != 0)
		close(*infd);
	*infd = fd;
}

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
