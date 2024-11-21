/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:52:49 by aarenas-          #+#    #+#             */
/*   Updated: 2024/11/21 12:28:56 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_check_redirs(t_cmd *cmd)
{
	if (!cmd->redir)
		return ;
	if (cmd->redir->type == INPUT_REDIRECT
		|| cmd->redir->type == HEREDOC)
		ft_in_redir(cmd->data, cmd->redir);
	else if (cmd->redir->type == OUTPUT_REDIRECT
		|| cmd->redir->type == OUTPUT_APPEND)
		ft_out_redir(cmd->redir);
}

void	ft_puterrorstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	exit(1);
}

void	ft_free(char **str)
{
	char	**ptr;

	if (!str)
		return ;
	ptr = str;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(str);
}

void	ft_freeanderror(t_data *lst)
{
	free(lst);
	perror("Error");
}
