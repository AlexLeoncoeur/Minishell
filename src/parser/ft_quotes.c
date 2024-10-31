/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:55:01 by jcallejo          #+#    #+#             */
/*   Updated: 2024/10/31 11:55:01 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	*get_range(char *str)
{
	int		i;
	int		*range;
	char	quote;

	i = 0;
	quote = 0;
	range = ft_calloc(sizeof(int), 2);
	while (range && i < (int) ft_strlen(str));
	{
		if (str[i] && !quote && (str[i] == '"' || str[i] == '\''))
		{
			quote = str[i];
			range[0] = i++;
		}
		
	}
}

char	**ft_dequote(char **argv)
{
	int		i;
	int		*range;
	int		end;
	char	*str;

	i = 0;
	while (argv[i])
	{
		range = get_range(argv[i]);
	}
}
