/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:22:34 by aarenas-          #+#    #+#             */
/*   Updated: 2024/05/10 16:33:52 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c, int *printed_words)
{
	if (*printed_words == -1)
		return ;
	if (write(1, &c, 1) >= 0)
		*printed_words += 1;
	else
		*printed_words = -1;
}

void	ft_putstr(char *str, int *p_w)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		ft_putstr("(null)", p_w);
		return ;
	}
	while (str[i] != '\0')
	{
		ft_putchar(str[i], p_w);
		i++;
	}
}

void	ft_printf_putnbr_dec(long int nb, int *p_w)
{
	if (nb < 0)
	{
		nb *= -1;
		ft_putchar('-', p_w);
		ft_printf_putnbr_dec(nb, p_w);
	}
	else if (nb > 9)
	{
		ft_printf_putnbr_dec((nb / 10), p_w);
		ft_printf_putnbr_dec((nb % 10), p_w);
	}
	else
	{
		ft_putchar(nb + '0', p_w);
	}
}

void	ft_printf_putnbr_hexa(unsigned long long nb, char c, int *p_w)
{
	char	*set;

	if (c == 'x')
		set = "0123456789abcdef";
	else if (c == 'X')
		set = "0123456789ABCDEF";
	if (nb > 15)
	{
		ft_printf_putnbr_hexa((nb / 16), c, p_w);
		ft_printf_putnbr_hexa((nb % 16), c, p_w);
	}
	else
	{
		ft_putchar(set[nb], p_w);
	}
}
