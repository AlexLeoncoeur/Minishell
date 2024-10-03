/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:22:55 by aarenas-          #+#    #+#             */
/*   Updated: 2024/10/02 11:38:39 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
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

typedef struct s_input
{
	int				type;
	char			*input;
	struct s_input	*next;
	struct s_input	*previous;
}	t_input;

typedef struct s_cmd
{
	char			*path;
	t_redir			*redir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct data
{
	t_input				*list;
	t_env				*env_var;
	t_cmd				*cmd;
	char				*line;
	char				**input;
	char				*heredoc;
	char				**envp;
	char				**argv;
	int					argc;
	int					status;
	int					exit_status;

}	t_data;

/* ------------------------ pipex/pipex_bonus ------------------------ */

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

/* ------------------------ built-ins/echo------------------------ */

void		ft_echo(char **matrix);

/* ------------------------ built-ins/pwd------------------------ */

void		ft_pwd(void);

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
void		ft_read_string(t_data *data);

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
void		ft_redirections(t_data *data, int *infd, int *outfd);

#endif