/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 02:31:52 by jcallejo          #+#    #+#             */
/*   Updated: 2024/10/31 02:31:52 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*str_replace_env(t_data *data, char *str)
{
	//hay que hacer que esto cambie las variables de entorno por su valor 
}

void	ft_parse_env(t_data *data, char **argv)
{
	int		i;
	int		j;
	char	quotes;

	i = -1;
	quotes = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if ((argv[i][j] == '"' || argv[i][j] == '\'') && !quotes)
				quotes = argv[i][j];
			else if (argv[i][j] == quotes)
				quotes = 0;
			if (argv[i][j] == '$' && (quotes == '"' || quotes == 0))
				argv[i] = str_replace_env(data, argv[i]);
			if (!argv[i][j])
				break ;
		}
	}
}
