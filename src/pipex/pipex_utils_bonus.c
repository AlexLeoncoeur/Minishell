/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:52:49 by aarenas-          #+#    #+#             */
/*   Updated: 2024/09/16 16:12:28 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_arg_list	*ft_define_lst(int argc, char **argv, char **envp)
{
	t_arg_list	*aux;

	aux = malloc(sizeof(t_arg_list));
	if (aux == NULL)
		return (NULL);
	aux->argc = argc;
	aux->argv = argv;
	aux->flags = NULL;
	aux->envp = envp;
	aux->next = NULL;
	return (aux);
}

void	ft_puterrorstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	exit(1);
}

void	ft_free(char **str)
{
	char	**ptr;

	if (!str)
		return ;
	ptr = str;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(str);
}

void	ft_freeanderror(t_arg_list *lst)
{
	free(lst);
	perror("Error");
}
