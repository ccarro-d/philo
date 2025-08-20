/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:40:14 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/08/20 18:40:37 by cesar            ###   ########.fr       */
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

	nbr = 0;
	if (*str == 32 || (*str >= 9 && *str <= 13) || *str == 43 || *str == 45)
	{
		printf("ERROR > Argument %d (%s): used signs/spaces\n", arg_nbr, rule);
		return (-1);
	}
	while (*str)
	{
		if (*str >= 48 && *str <= 57)
			nbr = (nbr * 10) + (*str - 48);
		else
		{
			printf("ERROR > Argument %d (%s) is not a number\n", arg_nbr, rule);
			return (-1);
		}
		str++;
	}
	if (nbr < 0 || nbr > INT_MAX)
	{
		printf("ERROR > Argument %d (%s): is out of range\n", arg_nbr, rule);
		return (-1);
	}
	return ((int)nbr);
}

int	print_error(char *err_msg)
{
	if (err_msg)
	{
		write(2, err_msg, ft_strlen(err_msg));
		write(2, "\n", 1);
	}
	return (1);
}
