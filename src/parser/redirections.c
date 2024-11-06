/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:36:51 by jcallejo          #+#    #+#             */
/*   Updated: 2024/11/06 11:37:15 by jcallejo         ###   ########.fr       */
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
		close(*infd);gi
	*infd = fd;
}

void	ft_redirections(t_data *data, pid_t pid)
{
	t_redir	*redir;
	//terminar redirections, tengo que reahcer el heredoc de nuevo porque no va a funcioanr con el nuevo parser
	//y tambien hay que hacer las funciones de añari comandos JAJA ME QUIERO MORIR
}
