/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils_chr_nbr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 12:58:16 by ccarro-d          #+#    #+#             */
/*   Updated: 2024/01/03 17:09:22 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunsint(unsigned int arg)
{
	char	c;
	int		r;

	r = 0;
	if (arg >= 0 && arg <= 4294967295)
	{
		if (arg <= 9)
			r += ft_putchr(arg + 48);
		if (arg > 9)
		{
			r += ft_putunsint(arg / 10);
			c = arg % 10 + 48;
			r += ft_putchr(c);
		}
	}
	return (r);
}

int	ft_putint(int arg)
{
	char	c;
	int		r;

	r = 0;
	if (arg == -2147483648)
		r += write(1, "-2147483648", 11);
	if (arg < 0 && arg != -2147483648)
	{
		r += ft_putchr('-');
		arg *= -1;
	}
	if (0 <= arg && arg <= 9)
		r += ft_putchr(arg + 48);
	if (arg > 9)
	{
		r += ft_putint(arg / 10);
		c = arg % 10 + 48;
		r += ft_putchr(c);
	}
	return (r);
}

int	ft_putstr(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		arg = "(null)";
	while (arg[i])
		ft_putchr(arg[i++]);
	return (i);
}

int	ft_putchr(int arg)
{
	return (write(1, &arg, 1));
}
