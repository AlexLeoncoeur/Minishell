/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:22:55 by aarenas-          #+#    #+#             */
/*   Updated: 2024/11/04 17:00:02 by aarenas-         ###   ########.fr       */
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

typedef struct s_cmd
{
	int				redir;
	char			*cmd;
	char			**argv;
	char			**env;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	int			error;
	t_cmd		*cmd;
}	t_data;

typedef struct s_env
{
	int				pos;
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_arg_list
{
	int				last;
	int				exit;
	int				error;
	int				builtin_done;
	int				argc;
	char			**argv;
	char			**envp;
	char			*heredoc;
	char			*input;
	t_env			*env;
	t_env			*env_export;
	t_env			*env_variables;
	t_cmd			*cmd;

}	t_arg_list;

/* ------------------------ pipex/pipex_bonus ------------------------ */

/**
 * @brief pipo
 * 
 * @param lst 
 * @param pos 
 * @return char* 
 */
//char		*ft_pathfinder(t_arg_list *lst, int pos);
void		ft_do_cmd(t_arg_list *lst);

/* ------------------------ pipex/pipex_utils_bonus ------------------------ */

//t_arg_list	*ft_define_lst(int argc, char **argv, char **envp);
void		ft_freeanderror(t_arg_list *lst);
void		ft_puterrorstr(char *str);
void		ft_free(char **str);

/* ------------------------ pipex/ft_here_doc ------------------------ */

void		ft_here_doc(int *pipefd, char **argv);
int			ft_openfile(char **argv, int argc);
int			ft_check_heredoc(char **argv);

/* ------------------------ pipex/last_cmd ------------------------ */

void		ft_do_last_cmd(t_cmd *lst);

/* ------------------------ built-ins/echo ------------------------ */

void		ft_echo(char **matrix);

/* ------------------------ built-ins/pwd ------------------------ */

void		ft_pwd(t_arg_list *data);

/* ------------------------ built-ins/exit ------------------------ */

void		ft_exit(char **argv, t_data *data);

/* ------------------------ built-ins/env ------------------------ */

void		ft_env(t_env *env);

/* ------------------------ built-ins/export ------------------------ */

void		ft_export(char *str, t_arg_list *data);
t_env		*ft_add_to_env(char *str, t_env *lst, int i);

/* ------------------------ built-ins/unset ------------------------ */

void		ft_unset(t_env **lst, char *name);

/* ------------------------ built-ins/cd ------------------------ */

void		ft_cd(t_arg_list *data, char *str);

/* ------------------------ env_lst.c ------------------------ */

t_cmd		*ft_lstlast_cmd(t_cmd *lst);
t_env		*ft_lstlast_tenv(t_env *lst);
t_env		*ft_lstnew_tenv(char *name, char *value, int i);
t_env		*ft_lst_env(char **envp, t_env *lst);
void		ft_lstadd_back_tenv(t_env **lst, t_env	*new);

/* ---------------------- check_built_ins.c ---------------------- */

void		ft_check_built_ins(t_arg_list *lst);

/* ---------------------- sort.c ---------------------- */

t_env		*ft_sort(t_env *lst);
int			ft_tenv_lstsize(t_env *lst);

/* ---------------------- finish.c ---------------------- */

void		ft_free_data(t_arg_list *data);

#endif