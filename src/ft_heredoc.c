/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:07:34 by jcallejo          #+#    #+#             */
/*   Updated: 2024/11/20 11:27:27 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static char	*heredoc_join(char *s1, char *s2, bool free_s1)
// {
// 	char	*ret;
// 	char	*aux;

// 	aux = ft_strjoin(s1, s2);
// 	ret = ft_strjoin(aux, "\n");
// 	free(aux);
// 	free(s2);
// 	if (free_s1)
// 		free(s1);
// 	return (ret);
// }

static void	read_heredoc(t_data *data)
{
	int		fd;
	char	*delim;
	char	*aux;

	data->heredoc = 0;
	delim = data->cmd->argv[1];
	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 1)
		return ;
	aux = readline("> ");
	while (aux && ft_strcmp(aux, delim) != 0)
	{
		ft_putstr_fd(aux, fd);
		free(aux);
		aux = readline("> ");
	}
	close(fd);
	free(aux);
}

int	ft_heredoc(t_data *data, t_redir *redir)
{
	while (redir)
	{
		if (redir->type == HEREDOC)
			read_heredoc(data);
		redir = redir->next;
	}
	return (1);
}
