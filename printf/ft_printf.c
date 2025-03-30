/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 12:58:16 by ccarro-d          #+#    #+#             */
/*   Updated: 2024/04/01 20:07:11 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putvar(char c, va_list args)
{
	if (c == '%')
		return (ft_putchr('%'));
	else if (c == 'c')
		return (ft_putchr(va_arg(args, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (c == 'i' || c == 'd')
		return (ft_putint(va_arg(args, int)));
	else if (c == 'u')
		return (ft_putunsint(va_arg(args, unsigned int)));
	else if (c == 'x')
		return (ft_putbase(va_arg(args, unsigned int), "0123456789abcdef"));
	else if (c == 'X')
		return (ft_putbase(va_arg(args, unsigned int), "0123456789ABCDEF"));
	else if (c == 'p')
		return (ft_putptr(va_arg(args, void *)));
	else
	{
		ft_printf("\e[1;91m""[Warning: incorrect format]\n""\e[0m");
		return (0);
	}
	return (0);
}

int	ft_printf(char const *to_print, ...)
{
	va_list	args;
	int		i;
	int		r;

	va_start(args, to_print);
	i = 0;
	r = 0;
	while (to_print[i])
	{
		if (to_print[i] == '%' && to_print[i + 1])
			r += ft_putvar(to_print[++i], args);
		else
		{
			ft_putchr(to_print[i]);
			r++;
		}
		i++;
	}
	va_end(args);
	return (r);
}
