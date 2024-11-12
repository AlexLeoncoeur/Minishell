/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:47:36 by jcallejo          #+#    #+#             */
/*   Updated: 2024/11/12 13:13:27 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_redir	*new_redir(int type, char *file)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->file = file;
	redir->type = type;
	redir->next = NULL;
	return (redir);
}

static t_redir	*add_back(t_redir *redir, t_redir *node)
{
	t_redir	*aux;

	if (!redir)
		redir = node;
	else
	{
		aux = redir;
		while (aux->next)
			aux = aux->next;
		aux->next = node;
	}
	return (redir);
}

static t_redir	*add_redir(char **argv)
{
	t_redir	*redirs;
	char	*aux;

	redirs = NULL;
	while (*argv)
	{
		aux = ft_strtrim(*argv, " ");
		if (ft_strnstr(aux, ">>", 2))
			redirs = add_back(redirs, new_redir(OUTPUT_APPEND,
						ft_strtrim(argv[0], " ")));
		else if (ft_strnstr(aux, "<<", 2))
			redirs = add_back(redirs, new_redir(HEREDOC,
						ft_strtrim(argv[0], " ")));
		else if (ft_strnstr(aux, "<", 1))
			redirs = add_back(redirs, new_redir(INPUT_REDIRECT,
						ft_strtrim(argv[0], " ")));
		else if (ft_strnstr(aux, ">", 1))
			redirs = add_back(redirs, new_redir(OUTPUT_REDIRECT,
						ft_strtrim(argv[0], " ")));
		argv++;
		free(aux);
	}
	return (redirs);
}

static char	**get_argv(char **argv)
{
	int		i;
	int		j;
	char	**aux;

	i = 0;
	while (argv[i] && !ft_strnstr(argv[i], ">>", 2)
		&& !ft_strnstr(argv[i], "<<", 2) && !ft_strnstr(argv[i], "<", 1)
		&& !ft_strnstr(argv[i], ">", 1))
		i++;
	aux = malloc(sizeof(char **) * (i + 1));
	if (!aux)
		return (NULL);
	j = 0;
	while (j < i)
	{
		aux[j] = ft_strtrim(argv[j], " ");
		j++;
	}
	aux[i] = 0;
	return (aux);
}

void	ft_add_cmd(t_data *data, t_cmd *cmd, char **argv)
{
	if (cmd->argv != NULL)
	{
		while (cmd->next)
			cmd = cmd->next;
		cmd = ft_new_cmd(data);
		cmd = cmd->next;
	}
	cmd->argv = get_argv(argv);
	cmd->path = ft_strtrim(argv[0], " ");
	cmd->redir = add_redir(argv);
}
