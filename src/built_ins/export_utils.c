/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:38:07 by aarenas-          #+#    #+#             */
/*   Updated: 2024/11/26 17:13:36 by aarenas-         ###   ########.fr       */
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
		data->env_export = ft_add_to_env(str, data->env_export);
	}
}
