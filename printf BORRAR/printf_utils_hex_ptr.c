/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils_hex_ptr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 12:58:16 by ccarro-d          #+#    #+#             */
/*   Updated: 2024/01/23 21:36:04 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_putbase(unsigned long arg, char *base)
{
	int				r;
	unsigned int	base_len;
	int				c;

	r = 0;
	if (arg < 0)
	{
		arg *= -1;
		arg = 4294967295 - arg;
	}
	base_len = ft_strlen(base);
	if (arg < base_len)
		return (r += ft_putchr(base[arg]));
	if (arg >= base_len)
	{
		r += ft_putbase(arg / base_len, base);
		c = arg % base_len;
		r += ft_putchr(base[c]);
	}
	return (r);
}

int	ft_putptr(void *ptr)
{
	int	r;

	r = write(1, "0x", 2);
	r += ft_putbase((unsigned long)ptr, "0123456789abcdef");
	return (r);
}
