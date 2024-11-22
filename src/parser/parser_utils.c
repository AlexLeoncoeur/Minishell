/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:35:35 by jcallejo          #+#    #+#             */
/*   Updated: 2024/11/22 13:31:06 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	ft_env_name_len(char *name)
{
	size_t	len;

	len = 0;
	while (ft_isalnum(name[len]) || name[len] == '_')
		len++;
	return (len);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*aux;
	unsigned char	*tmp;

	aux = (unsigned char *)s1;
	tmp = (unsigned char *)s2;
	i = 0;
	while ((aux[i] != '\0' && tmp[i] != '\0')
		&& aux[i] == tmp[i])
		i++;
	return (aux[i] - tmp[i]);
}

t_env	*ft_get_env(t_data *data, char *name)
{
	t_env	*current;

	current = data->env;
	if (!current)
		return ((t_env *)0);
	while (current->next)
	{
		if (!ft_strcmp(name, current->name))
			return (current);
		current = current->next;
	}
	if (!ft_strcmp(name, current->name))
		return (current);
	return ((t_env *)0);
}

char	ft_check_quote(char c, char quote)
{
	if (c == '\'' && !quote)
		return ('\'');
	else if (c == '\'')
		return (0);
	else if (c == '"' && !quote)
		return ('"');
	else if (c == '"')
		return (0);
	else
		return (quote);
}

void	ft_remove_redirs(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (*argv[i] == '<' || *argv[i] == '>')
		{
			argv[i] = 0;
			break ;
		}
		i++;
	}
}
