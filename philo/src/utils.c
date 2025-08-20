/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:40:14 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/08/20 20:52:49 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (n)
	{
		if (*str1 > *str2)
			return (1);
		if (*str1 < *str2)
			return (-1);
		if (*str1 == '\0' || *str2 == '\0')
			break ;
		str1++;
		str2++;
		n--;
	}
	return (0);
}

int	ft_atoi(char *str, char *rule, int arg_nbr)
{
	long long	nbr;

	if (*str == 32 || (*str >= 9 && *str <= 13) || *str == 43 || *str == 45)
		return (print_error_atoi(arg_nbr, rule, "used signs/spaces"));
	if (*str == '\0')
		return (print_error_atoi(arg_nbr, rule, "is not a number"));
	nbr = 0;
	while (*str)
	{
		if (*str >= 48 && *str <= 57)
			nbr = (nbr * 10) + (*str - 48);
		else
			return (print_error_atoi(arg_nbr, rule, "is not a number"));
		str++;
	}
	if (nbr < 0 || nbr > INT_MAX)
		return (print_error_atoi(arg_nbr, rule, "is out of range"));
	return ((int)nbr);
}
