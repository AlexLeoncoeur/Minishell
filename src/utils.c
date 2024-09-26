/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:35:35 by jcallejo          #+#    #+#             */
/*   Updated: 2024/09/26 23:23:32 by jcallejo         ###   ########.fr       */
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

char	*ft_get_env(char *input, t_data *data)
{
	
}

void	ft_replace_aux(t_input *input, int start, int end, char *val)
{
	
}
