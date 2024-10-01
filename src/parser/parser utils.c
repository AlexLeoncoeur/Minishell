/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:35:35 by jcallejo          #+#    #+#             */
/*   Updated: 2024/10/01 11:04:04 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_is_all_space(char *input)
{
	int	c;

	c = 0;
	while (input[c] && (input[c] == ' ' || input[c] == '\t'))
		c++;
	if (input[c] == '\0')
		return (1);
	return (0);
}

static int	ft_strcmp(const char *s1, const char *s2)
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

static char	*ft_get_var(char *env)
{
	int		i;
	char	*var;

	i = 0;
	while (env[i] != '=')
		i++;
	var = malloc(sizeof(char) * i + 1);
	if (!var)
		return NULL;
	i = 0;
	while (env[i] != '=')
	{
		var[i] = env[i];
		i++;
	}
	var[i] = 0;
	return (var);
	
}

char	*ft_get_env(char *input, t_data *data)
{
	int		i;
	char	*var;
	char	*aux;
	char	**val;

	i = 0;
	while(data->envp[i])
	{
		var = ft_get_var(data->envp[i]);
		if (ft_strcmp(var, input) == 0)
		{
			free(var);
			val = ft_split(data->envp[i], '=');
			aux = ft_strdup(val[1]);
			ft_clean_array(val);
			return(aux);
		}
		free(var);
		i++;
	}
	return (NULL);
}

void	ft_replace_aux(t_input *input, int start, int end, char *val)
{
	int		i;
	int		j;
	char	*aux;

	i = 0;
	j = 0;
	if (val == NULL)
		val = "";
	aux = malloc(sizeof(char) * ft_strlen(input->input) - (end - start)
		+ ft_strlen(val + 1));
	if (!aux)
		return ;
	while (i < start)
		aux[i++] = input->input[j++];
	j = 0;
	while (val[j])
		aux[i++] = val[j++];
	j = end;
	while (input->input[j])
		aux[i++] = input->input[j++];
	aux[i] = 0;
	free(input->input);
	input->input = aux;
}
