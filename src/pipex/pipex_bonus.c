/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:39:13 by aarenas-          #+#    #+#             */
/*   Updated: 2024/11/07 15:28:29 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_definitive_path(char **d_paths, char *command)
{
	char	*endl;
	char	*path;
	int		i;

	i = 0;
	/* if (lst->flags)
		ft_free(lst->flags); */
	//lst->flags = ft_split(lst->argv[pos], ' ');
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

static char	*ft_pathfinder(t_arg_list *lst, char *command)
{
	char	**d_paths;
	char	*path;
	int		i;

	i = 0;
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
		ft_puterrorstr("Error: Command not found\n");
	return (path);
}

static void	ft_execute_cmd(t_cmd *cmd, int *pipefd, int i, int *builtin_done)
{
	char	*path;

	if (i == -1)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
	}
	else
		dup2(cmd->redir, STDOUT_FILENO);
	//Si el redir es == HEREDOC ejecutar ft_heredoc, ft_in_redir(data, cmd->redir), dup2(fd, STDIN_FILENO);
	ft_check_built_ins(cmd, builtin_done);
	if (*builtin_done == 1)
	{
		path = cmd->cmd;
		if (execve(path, cmd->argv, cmd->envp) < 0)
		{
			perror("minishell: executer");
			free(path);
			ft_free(cmd->argv);
			exit(1);
		}
	}
}

void	ft_do_cmd(t_arg_list *lst)
{
	int		pipefd[2];
	int		child;
	t_cmd	*aux;

	//dup2(lst->cmd->redir, STDIN_FILENO); //Si hay un redir de entrada
	aux = lst->cmd;
	while (aux->next)
	{
		if (pipe(pipefd) == -1)
			perror("Error");
		child = fork();
		if (child == -1)
			perror("Error");
		else if (child == 0 && aux->redir >= 0)  //
			ft_execute_cmd(aux, 0, 0, &lst->builtin_done); //	Dividir en otra función
		else if (child == 0 && aux->redir == -1) //
			ft_execute_cmd(aux, pipefd, -1, &lst->builtin_done);
		if (waitpid(-1, NULL, 0) == -1)
		{
			perror("Error");
			exit(1);
		}
		close(pipefd[1]); //poner dentro del if de abajo
		if (aux->redir < 0)
			dup2(pipefd[0], STDIN_FILENO);
		aux = aux->next;
	}
}

static t_cmd	*ft_test_cmd(t_arg_list *data)
{
	t_cmd	*prueba;
	char	*arg;

	prueba = malloc(sizeof(t_cmd));
	arg = ft_strdup("..");
	prueba->argv = malloc(sizeof(char *) * 2);
	prueba->next->argv[1] = NULL;
	printf("pipo por favor\n");
	prueba->next->argv[0] = arg;
	prueba->envp = data->envp;
	prueba->redir = -1;
	prueba->next = malloc(sizeof(t_cmd));
	prueba->env = NULL;
	prueba->env_export = NULL;
	prueba->data = data;
	prueba->next->argv = NULL;
/* 	prueba->next->argv[1] = NULL;
	prueba->next->argv[0] = arg; */
	prueba->next->envp = data->envp;
	prueba->next->redir = -1;
	prueba->next->next = NULL;
	prueba->next->env = NULL;
	prueba->next->env_export = NULL;
	prueba->data = data;
	return (prueba);
}

int	main(int argc, char **argv, char **envp)
{
	t_arg_list	*data;
	//t_arg_list	*lst;

	//lst = ft_define_lst(argc, argv, envp);
	data = malloc(sizeof(t_arg_list));
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->cmd = ft_test_cmd(data);
	data->cmd->cmd = ft_pathfinder(data, "cd");
	data->builtin_done = 0;
	data->cmd->next->cmd = "pwd";
	//data->cmd->next->cmd = ft_pathfinder(data, "exit");
	//data->cmd->next->argv[0] = data->cmd->next->cmd;
	/* if (data->cmd->redir == -1)
		exit(1); */
	if (data->cmd && !data->cmd->next)
	{
		if (data->cmd->redir >= 0)
			dup2(data->cmd->redir, STDOUT_FILENO);
		ft_check_built_ins(data->cmd, &data->builtin_done);
	}
	if (data->cmd && !data->cmd->next && data->builtin_done == 1)
		ft_do_last_cmd(data->cmd, &data->builtin_done);
	else
	{
		ft_do_cmd(data);
		dup2(1, STDOUT_FILENO);
		if (ft_lstlast_cmd(data->cmd)->redir >= 0)
			dup2(ft_lstlast_cmd(data->cmd)->redir, STDOUT_FILENO);
		ft_do_last_cmd(ft_lstlast_cmd(data->cmd), &data->builtin_done);
	}
	return (0);
}

//	Hacer funcion de prueba que cree e inicialice la lista de comandos y probar cositas

//Hacer comprobacion si las variables de entorno
//	estan vacias entonces usar funcion que las coge
//Usar la estructura nueva para llamar y usar todas estas
//	funciones antes de avanzar
//Pedirle a jcallejo que anada la funcion de env en el main y
//	que lo guarde en la estructura t_data
//No es necesario gestionar la falta de variables de entorno, si no hay
//	da error y listo