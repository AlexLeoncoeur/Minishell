/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:38:07 by aarenas-          #+#    #+#             */
/*   Updated: 2024/11/26 23:16:14 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_str_is_alphanum(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		if (ft_isalnum(str[i++]) == 0)
			return (0);
	return (1);
}

void	ft_check_and_add(t_data *data, char *str)
{
	if (str && ft_isdigit(str[0]) == 0
		&& ft_search_replace(&data->env, str) == 1)
	{
		data->env = ft_add_to_env(str, data->env);
		//data->env_export = ft_add_to_env(str, data->env_export);
	}
}

static int	custom_lstsize(t_env *env)
{
	int	i;
	
	i = 0;
	while (env->next)
	{
		i++;
		env = env->next;
	}
	return (++i);
}

void	ft_parse_list(t_data *data)
{
	char	**envp;
	char	*aux;
	t_env	*eaux;
	int		i;

	i = 0;
	envp = malloc(sizeof(char **) * (custom_lstsize(data->env) + 1));
	if (!envp)
		return ;
	eaux = data->env;
	ft_cl_ar(data->envp);
	while (eaux)
	{
		aux = ft_strjoin(eaux->name, "=");
		envp[i] = ft_strjoin(aux, eaux->value);
		i++;
		free(aux);
		eaux = eaux->next;
	}
	envp[i] = 0;
	data->envp = envp;
}
