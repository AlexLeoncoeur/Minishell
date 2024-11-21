/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:39:13 by aarenas-          #+#    #+#             */
/*   Updated: 2024/11/21 12:54:45 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_definitive_path(char **d_paths, char *command)
{
	char	*endl;
	char	*path;
	int		i;

	i = 0;
	endl = ft_strjoin("/", command);
	path = ft_strjoin(d_paths[0], endl);
	while (d_paths[i] && access(path, X_OK) < 0)
	{
		free(path);
		path = ft_strjoin(d_paths[i], endl);
		i++;
	}
	if (d_paths[i])
		return (free(endl), path);
	free(path);
	return (free(endl), NULL);
}

char	*ft_pathfinder(t_data *lst, char *command)
{
	char	**d_paths;
	char	*path;
	int		i;

	i = 0;
	if (ft_strncmp(command, "./", 2) == 0)
		return (&command[2]); //join de pwd y command para la ruta absoluta
	while (ft_strncmp(lst->envp[i], "PATH=", 5) != 0)
		i++;
	if (lst->envp[i] == NULL)
		return (NULL);
	path = ft_substr(lst->envp[i], 5, ft_strlen(lst->envp[i]) - 5);
	if (path == NULL)
		return (NULL);
	d_paths = ft_split(path, ':');
	free(path);
	path = ft_definitive_path(d_paths, command);
	if (!path)
		return (lst->error = 127, NULL);
	return (path);
}

static void	ft_execute_cmd(t_cmd *cmd, int *pipefd, int *builtin_done)
{
	char	*path;

	if (cmd->redir)
		ft_check_redirs(cmd);
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
	}
	ft_check_built_ins(cmd, builtin_done);
	if (*builtin_done == 1)
	{
		path = ft_pathfinder(cmd->data, cmd->path);
		if (execve(path, cmd->argv, cmd->data->envp) < 0)
		{
			perror("minishell: executer");
			cmd->data->error = errno;
			free(cmd->path);
			ft_free(cmd->argv);
			exit(1);
		}
	}
	exit(0);
	(void)path;
}

int	ft_do_cmd(t_data *lst)
{
	int		pipefd[2];
	int		child;
	t_cmd	*aux;

	aux = lst->cmd;
	while (aux->next)
	{
		if (pipe(pipefd) == -1)
			perror("Error");
		child = fork();
		if (child == -1)
			perror("Error");
		else if (child == 0)
			ft_execute_cmd(aux, pipefd, &lst->builtin_done);
		if (waitpid(-1, NULL, 0) == -1)
		{
			lst->error = 1;
			perror("Error");
		}
		close(pipefd[1]);
		if (!aux->next->redir || aux->next->redir->type != INPUT_REDIRECT)
			dup2(pipefd[0], STDIN_FILENO);
		aux = aux->next;
	}
	return (pipefd[0]);
}

int	ft_executer(t_data *data)
{
	int	fd;
	int	stdfd;

	stdfd = dup(STDIN_FILENO);
	if (data->cmd && !data->cmd->next)
	{
		if (data->cmd->redir)
			ft_check_redirs(data->cmd);
		ft_check_built_ins(data->cmd, &data->builtin_done);
		if (data->builtin_done == 1)
			ft_do_last_cmd(data->cmd, &data->builtin_done);
	}
	else if (data->cmd && data->cmd->next)
	{
		fd = ft_do_cmd(data);
		if (ft_lstlast_cmd(data->cmd)->redir)
			ft_check_redirs(ft_lstlast_cmd(data->cmd));
		ft_do_last_cmd(ft_lstlast_cmd(data->cmd), &data->builtin_done);
		close(fd);
	}
	return (dup2(stdfd, STDIN_FILENO), 0);
}

/*testing*/

/* static t_cmd	*ft_test_cmd(t_data *data)
{
	t_cmd	*prueba;
	char	*arg;

	prueba = malloc(sizeof(t_cmd));
	arg = ft_strdup("..");
	prueba->argv = malloc(sizeof(char *) * 2);
	prueba->argv[1] = NULL;
	prueba->argv[0] = arg;
	prueba->envp = data->envp;
	prueba->redir = -1;
	prueba->next = malloc(sizeof(t_cmd));
	prueba->env = NULL;
	prueba->env_export = NULL;
	prueba->data = data;
	prueba->next->argv = NULL;
	prueba->next->argv[1] = NULL;
	prueba->next->argv[0] = arg;
	prueba->next->envp = data->envp;
	prueba->next->redir = -1;
	prueba->next->next = NULL;
	prueba->next->env = NULL;
	prueba->next->env_export = NULL;
	prueba->data = data;
	return (prueba);
} */

	/* t_data	*data;
	//t_data	*lst;

	//lst = ft_define_lst(argc, argv, envp);
	data = malloc(sizeof(t_data));
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->cmd = ft_test_cmd(data);
	data->cmd->path = "cd";
	data->builtin_done = 0;
	data->cmd->next->cmd = "pwd";
	//data->cmd->next->cmd = ft_pathfinder(data, "exit");
	//data->cmd->next->argv[0] = data->cmd->next->cmd; */