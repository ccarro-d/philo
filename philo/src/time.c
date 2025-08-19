/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:40:19 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/08/19 18:46:07 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long	get_time(void)
{
	struct timeval	tv;
	long long		ms;

	if (gettimeofday(&tv, NULL))
	{
		print_error("Error > No se puedo obtener timestamp");
		return (0);
	}
	ms = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
	return (ms);
}

void	precise_usleep(long long time_ms, long long start)
{
	long long	fraction;

	fraction = (long long)(time_ms * 6 / 10);
	usleep(fraction * 1e3);
	while (get_time() - start < time_ms)
		usleep(100);
	return ;
}
