/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:28:18 by aarenas-          #+#    #+#             */
/*   Updated: 2024/10/17 10:30:50 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static void	ft_free_tenv(t_env *lst)
{
	
}

void	ft_free_data(t_arg_list *data)
{
	ft_free_tenv(env);
	ft_free_tenv(env_export);
}
