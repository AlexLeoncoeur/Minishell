/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:33:35 by aarenas-          #+#    #+#             */
/*   Updated: 2024/09/17 13:53:31 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_echo(char **matrix)
{
	int	flag;
	int	i;
	int	j;

	flag = 0;
	i = 0;
	j = 0;
	if (matrix[0][0] == '-' && matrix[0][1] == 'n')
		flag = 1;
	while (matrix[i][0] == '-' && matrix[i][1] == 'n')
	{
		while (matrix[i][j] == 'n')
			j++;
		if (matrix[i][j])
			break ;
		i++;
	}
	j = 0;
	while (matrix[i][j])
	{
		ft_putstr_fd(matrix[i], STDOUT_FILENO);
		i++;
	}
	if (flag == 1)
		ft_putchar('\n');
}
