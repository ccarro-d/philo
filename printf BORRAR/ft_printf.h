/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:55:17 by ccarro-d          #+#    #+#             */
/*   Updated: 2023/11/23 20:18:01 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// PRINT TYPES FUNCTIONS
int				ft_putchr(int arg);
int				ft_putstr(char *arg);
int				ft_putint(int arg);
int				ft_putunsint(unsigned int arg);
int				ft_putptr(void *ptr);
int				ft_putbase(unsigned long arg, char *base);
unsigned int	ft_strlen(const char *s);

// PRINTF MAIN FUNCTIONS
int				ft_printf(char const *to_print, ...);
int				ft_putvar(char c, va_list args);

#endif
