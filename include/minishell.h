/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:22:55 by aarenas-          #+#    #+#             */
/*   Updated: 2024/10/29 10:51:28 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>

# define NORMAL_INPUT		0
# define SINGLE_QUOTE 		1
# define DOUBLE_QUOTE 		2
# define HEREDOC	  		3
# define OUTPUT_APPEND		4
# define INPUT_REDIRECT 	5
# define OUTPUT_REDIRECT	6
# define PIPE				7

typedef struct s_redir
{
	int				type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			*path;
	char			**argv;
	t_redir			*redir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	t_env	*env_variables;
	t_cmd	*cmd;
	char	*input;
	char	*heredoc;
	char	**envp;
	int		last;
	int		exit;
	int		error;
	t_env	*env;
	t_env	*env_export;
}	t_data;

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
t_env		*ft_add_to_env(char *str, t_env *lst, int i);

/* ------------------------ built-ins/unset ------------------------ */

void		ft_unset(t_env **lst, char *name);

/* ------------------------ env_lst.c ------------------------ */

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

/* ------------------------ Initializer------------------------ */

/**
 * @brief Initializes data struct
 * 
 * @param data 
 * @return int 
 */
int			ft_init(t_data *data, int argc, char **argv, char **envp);

/* ------------------------ Lexer------------------------ */

/**
 * @brief Reads text inputed by user and processes it
 * 
 * @param data 
 * @return int 
 */
int			ft_read_string(t_data *data);

/**
 * @brief Checks if line is comprised only of tabs or spaces
 * 
 * @param input 
 * @return int 
 */
int			ft_is_all_space(char *input);

/* ------------------------ Parser------------------------ */

/**
 * @brief Parses the line of input
 * 
 * @param data 
 */
void		ft_parser(t_data *data);

/* ------------------------ Cleanup------------------------ */
/**
 * @brief Frees inside array and then all of it
 * 
 * @param array 
 */
void		ft_clean_array(char **array);

/* ------------------------ Redirections------------------------ */
/**
 * @brief Determines what type of redirection it is and calls respective 
 * function
 * 
 * @param data 
 * @param infd 
 * @param outfd 
 */
void		ft_redirections(t_data *data, int *infd, int *outfd);

/* ------------------------ Heredoc------------------------ */
/**
 * @brief Creates heredoc and manages it
 * 
 * @param current 
 * @param infd 
 * @param data 
 */
void		ft_heredoc(t_input *current, int *infd, t_data *data);

/* ------------------------ Utils------------------------ */
/**
 * @brief Gets env variable value and returs it
 * 
 * @param input 
 * @param data 
 * @return char* 
 */
t_env		*ft_get_env(char *input, t_data *data);

/**
 * @brief Compates two strs and returns difference
 * 
 * @param s1 
 * @param s2 
 * @return int 
 */
int			ft_strcmp(const char *s1, const char *s2);

/* ------------------------ Signals------------------------ */
void		signal_setter(void);
void		ft_active_setter(int i);

#endif