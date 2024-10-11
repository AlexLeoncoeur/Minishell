/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:22:55 by aarenas-          #+#    #+#             */
/*   Updated: 2024/10/11 11:14:24 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>

typedef struct s_cmd_list
{
	char	**cmd;
	int		fd;
}	t_cmd_list;

typedef struct s_data
{
	int			error;
	t_cmd_list	*cmd;
}	t_data;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_arg_list
{
	int				argc;
	char			**argv;
	char			**flags;
	char			**envp;
	t_env			*env;
	t_env			*env_export;

}	t_arg_list;

/* ------------------------ pipex/pipex_bonus ------------------------ */

/**
 * @brief pipo
 * 
 * @param lst 
 * @param pos 
 * @return char* 
 */
char		*ft_pathfinder(t_arg_list *lst, int pos);

/* ------------------------ pipex/pipex_utils_bonus ------------------------ */

t_arg_list	*ft_define_lst(int argc, char **argv, char **envp);
void		ft_freeanderror(t_arg_list *lst);
void		ft_puterrorstr(char *str);
void		ft_free(char **str);

/* ------------------------ pipex/ft_here_doc ------------------------ */

void		ft_here_doc(int *pipefd, char **argv);
int			ft_openfile(char **argv, int argc);
int			ft_check_heredoc(char **argv);

/* ------------------------ pipex/last_cmd ------------------------ */

void		ft_do_last_cmd(t_arg_list *lst, int fd);

/* ------------------------ built-ins/echo ------------------------ */

void		ft_echo(char **matrix);

/* ------------------------ built-ins/pwd ------------------------ */

void		ft_pwd(t_data *data);

/* ------------------------ built-ins/exit ------------------------ */

void		ft_exit(char **argv, t_data *data);

/* ------------------------ built-ins/env ------------------------ */

void		ft_env(t_env *env);

/* ------------------------ built-ins/export ------------------------ */

void		ft_export(char *str, t_arg_list *data);
void		ft_add_to_env(char *str, t_arg_list *data);

/* ------------------------ env_lst.c ------------------------ */

t_env		*ft_lstlast_tenv(t_env *lst);
t_env		*ft_lstnew_tenv(char *name, char *value);
void		ft_lst_env(t_arg_list *data);
void		ft_lstadd_back_tenv(t_env **lst, t_env	*new);

/* ---------------------- check_built_ins.c ---------------------- */

void		ft_check_built_ins(t_arg_list *lst);

/* ---------------------- sort.c ---------------------- */

t_env		*ft_sort(t_env *lst);

#endif