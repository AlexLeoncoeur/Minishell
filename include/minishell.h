/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:22:55 by aarenas-          #+#    #+#             */
/*   Updated: 2024/11/11 12:59:40 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "../include/colors.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <limits.h>
# include <signal.h>
# include <fcntl.h>

# define INPUT_REDIRECT 	1
# define OUTPUT_REDIRECT	2
# define OUTPUT_APPEND		3
# define HEREDOC	  		4

typedef struct s_data		t_data;
typedef struct s_env		t_env;

typedef struct s_redir
{
	int				type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	t_data			*data;
	t_redir			*redir;
	char			*path;
	char			**argv;
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
	t_cmd		*cmd;
	t_env		*env;
	t_env		*env_export;
	char		*input;
	char		*heredoc;
	char		**envp;
	int			error;
	int			builtin_done;
	int			argc;
}	t_data;

/* ------------------------ pipex/pipex_bonus ------------------------ */

/**
 * @brief pipo
 * 
 * @param lst 
 * @param pos 
 * @return char* 
 */
//char		*ft_pathfinder(t_data *lst, int pos);
void		ft_do_cmd(t_data *lst);
int			ft_executer(t_data *data);

/* ------------------------ pipex/pipex_utils_bonus ------------------------ */

//t_data	*ft_define_lst(int argc, char **argv, char **envp);
void		ft_freeanderror(t_data *lst);
void		ft_check_redirs(t_cmd *cmd);
void		ft_puterrorstr(char *str);
void		ft_free(char **str);

/* ------------------------ pipex/last_cmd ------------------------ */

void		ft_do_last_cmd(t_cmd *lst, int *builtin_done);

/* ------------------------ built-ins/echo ------------------------ */

void		ft_echo(char **matrix);

/* ------------------------ built-ins/pwd ------------------------ */

void		ft_pwd(t_data *data);

/* ------------------------ built-ins/exit ------------------------ */

void		ft_exit(char **argv, t_data *data);

/* ------------------------ built-ins/env ------------------------ */

void		ft_env(t_env *env);

/* ------------------------ built-ins/export ------------------------ */

void		ft_export(char *str, t_data *data);
t_env		*ft_add_to_env(char *str, t_env *lst);

/* ------------------------ built-ins/unset ------------------------ */

void		ft_unset(t_env **lst, char *name);

/* ------------------------ built-ins/cd ------------------------ */

void		ft_cd(t_data *data, char **str);

/* ------------------------ env_lst.c ------------------------ */

t_cmd		*ft_lstlast_cmd(t_cmd *lst);
t_env		*ft_lstlast_tenv(t_env *lst);
t_env		*ft_lstnew_tenv(char *name, char *value);
t_env		*ft_lst_env(char **envp, t_env *lst);
void		ft_lstadd_back_tenv(t_env **lst, t_env	*new);

/* ---------------------- check_built_ins.c ---------------------- */

void		ft_check_built_ins(t_cmd *cmd, int *builtin_done);

/* ---------------------- sort.c ---------------------- */

t_env		*ft_sort(t_env *lst);
int			ft_tenv_lstsize(t_env *lst);

/* ---------------------- finish.c ---------------------- */

void		ft_free_data(t_data *data);

void		ft_in_redir(t_data *data, t_redir *redir);

void		ft_out_redir(t_redir *redir);

/* ---------------------- Parser/Lexer ---------------------- */

/**
 * @brief Initializes data structure
 * 
 * @param data 
 * @param envp 
 * @return int 
 */
int			ft_init(t_data *data, char **envp);

/**
 * @brief Reads input string
 * 
 * @param data 
 * @return int 
 */
int			ft_read_string(t_data *data);

/**
 * @brief Main parser function to create cmd struct
 * 
 * @param data 
 * @return t_cmd* 
 */
t_cmd		*ft_parser(t_data *data);

/**
 * @brief Adds new node to cmd list
 * 
 * @return t_cmd* 
 */
t_cmd		*ft_new_cmd(void);

/**
 * @brief Gets enviromental variable
 * 
 * @param data 
 * @param name 
 * @return t_env* 
 */
t_env		*ft_get_env(t_data *data, char *name);

/**
 * @brief Split to get each command and it's args sepparatelly
 * 
 * @param str 
 * @return char** 
 */
char		**ft_pipesplit(char *str);

/**
 * @brief Splits based on spaces to separate every part of the cmds and args
 * 
 * @param str 
 * @return char** 
 */
char		**ft_minisplit(char *str);

/**
 * @brief Parses env var
 * 
 * @param data 
 * @param argv 
 */
void		ft_parse_env(t_data *data, char **argv);

/**
 * @brief Strlen for env variables
 * 
 * @param name 
 * @return size_t 
 */
size_t		ft_env_name_len(char *name);

/**
 * @brief Cleans arrays, just that
 * 
 * @param array 
 */
void		ft_clean_array(char **array);

/**
 * @brief Cleans cmd struct
 * 
 * @param data 
 */
void		ft_clean_cmd(t_data *data);

/**
 * @brief Guess what, removes quotes
 * 
 * @param argv 
 * @return char** 
 */
char		**ft_dequote(char **argv);

/**
 * @brief Classifies and parses all redirections
 * 
 * @param data 
 * @param pid 
 */
void		ft_redirections(t_data *data, pid_t pid);

/**
 * @brief The function that really fills t_cmd
 * 
 * @param cmd 
 * @param argv 
 */
void		ft_add_cmd(t_cmd *cmd, char **argv);

/**
 * @brief Main function to manage heredoc
 * 
 * @param data 
 * @param redir 
 * @return int 
 */
int			ft_heredoc(t_data *data, t_redir *redir);

/**
 * @brief Because in libft we only make strncmp
 * 
 * @param s1 
 * @param s2 
 * @return int 
 */
int			ft_strcmp(const char *s1, const char *s2);

/**
 * @brief Get enviromental values
 * 
 * @param data 
 * @param name 
 * @return t_env* 
 */
t_env		*ft_get_env(t_data *data, char *name);

/**
 * @brief Check for quote characters
 * 
 * @param c 
 * @param quote 
 * @return char 
 */
char		ft_check_quote(char c, char quote);

/**
 * @brief Initializes signals
 * 
 */
void		ft_init_signals(void);

/**
 * @brief Sets main variable flag to 1 when starting the program
 * 
 * @param i 
 */
void		ft_set_flag(int i);

#endif