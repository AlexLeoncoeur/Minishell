/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:39:13 by aarenas-          #+#    #+#             */
/*   Updated: 2024/09/18 11:23:07 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_definitive_path(t_arg_list *lst, int pos, char **d_paths)
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
}

static void	ft_execute_cmd(t_arg_list *lst, int *pipefd, int i)
{
	char	*path;

	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	path = ft_pathfinder(lst, i);
	if (execve(path, lst->flags, lst->envp) < 0)
	{
		perror(lst->flags[1]);
		free(path);
		ft_free(lst->flags);
		exit(1);
	}
}

static void	ft_do_cmd(t_arg_list *lst, int fd, int i)
{
	int		pipefd[2];
	int		child;

	dup2(fd, STDIN_FILENO);
	while (i < lst->argc - 2)
	{
		if (pipe(pipefd) == -1)
			perror("Error");
		child = fork();
		if (child == 0)
			ft_execute_cmd(lst, pipefd, i);
		else if (child == -1)
			perror("Error");
		if (waitpid(-1, NULL, 0) == -1)
		{
			perror("Error");
			exit(1);
		}
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	int			fd;
	t_arg_list	*lst;

	//ft_check_built-in
	if (ft_strncmp(argv[1], "echo\0", 5) == 0)
	{
		ft_echo(&argv[2]);
		return (0);
	}
	if (ft_strncmp(argv[1], "pwd\0", 4) == 0)
	{
		ft_pwd();
		return (0);
	}
	fd = ft_check_heredoc(argv);
	if (fd == -1)
		exit(1);
	lst = ft_define_lst(argc, argv, envp);
	if (ft_strncmp(argv[1], "here_doc\0", 9) == 0)
		ft_do_cmd(lst, fd, 3);
	else
		ft_do_cmd(lst, fd, 2);
	close(fd);
	fd = ft_openfile(argv, argc);
	if (fd == -1)
		return (ft_freeanderror(lst), 1);
	dup2(fd, STDOUT_FILENO);
	ft_do_last_cmd(lst, fd);
	return (0);
}
// Hacer comprobacion si las variables de entorno
//estan vacias entonces usar funcion que las coge