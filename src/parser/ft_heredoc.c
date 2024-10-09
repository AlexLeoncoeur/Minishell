/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:07:34 by jcallejo          #+#    #+#             */
/*   Updated: 2024/10/09 11:32:34 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_tmp_path(t_data *data)
{
	char	*shell;
	char	*aux;

	aux = ft_get_env("SHELL", data);
	shell = ft_strtrim(aux, "minishell");
	free(aux);
	aux = ft_strjoin(shell, "/tmp/.heredoc_minishell.tmp");
	free(shell);
	return (aux);
}

static char	*ft_get_delim(t_input *current)
{
	char	**tmp;
	char	*aux;

	tmp = ft_split(current->input, ' ');
	aux = ft_strjoin(tmp[1], "\n");
	ft_clean_array(tmp);
	return (aux);
}

void	ft_heredoc(t_input *current, int *infd, t_data *data)
{
	int		fd;
	char	*delim;
	char	*line;
	char	*shell;

	delim = ft_get_delim(current);
	shell = ft_tmp_path(data);
	fd = open(shell, O_WRONLY | O_CREAT | O_TRUNC);
	line = get_next_line(STDIN_FILENO);
	while (ft_strcmp(line, delim) != 0)
	{
		ft_putstr_fd(line, fd);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	close(fd);
	fd = open(shell, O_RDONLY);
	free(shell);
	free(line);
	free(delim);
	if (*infd != 0)
		close(*infd);
	*infd = fd;
}
