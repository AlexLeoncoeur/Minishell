/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:07:34 by jcallejo          #+#    #+#             */
/*   Updated: 2024/11/11 11:22:26 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*heredoc_join(char *s1, char *s2, bool free_s1)
{
	char	*ret;
	char	*aux;

	aux = ft_strjoin(s1, s2);
	ret = ft_strjoin(aux, "\n");
	free(aux);
	free(s2);
	if (free_s1)
		free(s1);
	return (ret);
}

static void	read_heredoc(t_data *data, t_redir *redir)
{
	int		fd;
	char	*aux;

	data->heredoc = 0;
	aux = 0;
	while (1)
	{
		aux = readline("> ");
		if (!aux || ft_strcmp(aux, redir->file))
			break ;
		if (!data->heredoc)
			data->heredoc = heredoc_join("", aux, false);
		else
			data->heredoc = heredoc_join(data->heredoc, aux, true);
	}
	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 1)
		return ;
	write (fd, data->heredoc, ft_strlen(data->heredoc));
	close (fd);
	free(redir->file);
	free (data->heredoc);
	redir->file = ft_strdup(".heredoc_tmp");
	redir->type = INPUT_REDIRECT;
}

int	ft_heredoc(t_data *data, t_redir *redir)
{
	if (!redir || !redir->file)
		return (1);
	while (redir)
	{
		if (redir->type == HEREDOC)
			read_heredoc(data, redir);
		redir = redir->next;
	}
	return (1);
}
