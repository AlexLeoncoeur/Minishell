/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:33:13 by jcallejo          #+#    #+#             */
/*   Updated: 2024/10/31 01:33:13 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*ft_new_cmd(void)
{
	t_cmd	*cmd;

	cmd = mallox(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->path = NULL;
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*ft_parser(t_data *data)
{
	char	**pipes;
	char	**argv;
	int		i;
	t_cmd	*cmd;

	i = 0;
	if (!ft_isalpha(data->input) && *data->input != '.' && *data->input != '/'
		&& *data->input != '"' && *data->input != '\'')
		return (NULL);
	pipes = ft_pipesplit(data->input);
	cmd = ft_new_cmd();
	while (pipes[i])
	{
		argv = ft_minisplit(pipes[i]);
		ft_parse_env(data, argv);
	}
}
