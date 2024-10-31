/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:39:13 by aarenas-          #+#    #+#             */
/*   Updated: 2024/10/31 13:37:09 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* static char	*ft_definitive_path(t_arg_list *lst, int pos, char **d_paths)
{
	char	*endl;
	char	*path;
	int		i;

	i = 0;
	if (lst->flags)
		ft_free(lst->flags);
	lst->flags = ft_split(lst->argv[pos], ' ');
	i = 0;
	endl = ft_strjoin("/", lst->flags[0]);
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

char	*ft_pathfinder(t_arg_list *lst, int pos)
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
	path = ft_definitive_path(lst, pos, d_paths);
	if (!path)
		ft_puterrorstr("Error: Command not found\n");
	return (path);
} */

static void	ft_execute_cmd(t_arg_list *lst, int *pipefd, int i) //Modificar para que si recibe un -1 use el redir como standar
{
	char	*path;

	if (pipefd >= 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
	}
	else
		dup2(lst->cmd->redir, STDOUT_FILENO);
	path = ft_pathfinder(lst, i);
	if (execve(path, lst->flags, lst->envp) < 0)
	{
		perror(lst->flags[1]);
		free(path);
		ft_free(lst->flags);
		exit(1);
	}
}

void	ft_do_cmd(t_arg_list *lst)
{
	int		pipefd[2];
	int		child;
	t_cmd	*aux;

	dup2(lst->cmd->redir, STDIN_FILENO); //Si hay un redir de entrada
	aux = lst->cmd;
	while (aux)
	{
		if (pipe(pipefd) == -1)
			perror("Error");
		child = fork();
		if (child == -1)
			perror("Error");
		else if (child == 0 && aux->redir > 0)  //
			ft_execute_cmd(aux, aux->redir, i); //	Dividir en otra función
		else if (child == 0 && aux->redir == 0) //
			ft_execute_cmd(aux, pipefd, i);
		if (waitpid(-1, NULL, 0) == -1)
		{
			perror("Error");
			exit(1);
		}
		close(pipefd[1]); //poner dentro del if de abajo
		if (aux->redir > 0)
			dup2(pipefd[0], STDIN_FILENO);
		aux = aux->next;
	}
}

int	ft_executer(t_arg_list *data)
{
	//t_arg_list	*lst;

	//lst = ft_define_lst(argc, argv, envp);
	if (data->cmd->redir == -1)
		exit(1);
	if (data->cmd && !data->cmd->next)
	{
		dup2(data->cmd->redir, STDOUT_FILENO);
		ft_check_built_ins(data);
	}
	else if (data->cmd && data->builtin_done == 1)
		ft_do_last_cmd(data->cmd);
	else
	{
		ft_do_cmd(data);
		dup2(ft_lstlast_cmd()->redir, STDOUT_FILENO);
		ft_do_last_cmd(data, fd);
	}
	return (0);
}
//Hacer comprobacion si las variables de entorno
//	estan vacias entonces usar funcion que las coge
//Usar la estructura nueva para llamar y usar todas estas
//	funciones antes de avanzar
//Pedirle a jcallejo que anada la funcion de env en el main y
//	que lo guarde en la estructura t_data
//No es necesario gestionar la falta de variables de entorno, si no hay
//	da error y listo