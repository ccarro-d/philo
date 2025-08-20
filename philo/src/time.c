/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:40:19 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/08/20 01:02:59 by cesar            ###   ########.fr       */
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

void	watcher_usleep(t_rules *rules, long long time_ms, long long start)
{
	long long	end;
	long long	now;
	long long	remain;

	end = start + time_ms;
	while (continue_simulation(rules))
	{
		now = get_time();
		if (now >= end)
			break ;
		remain = end - now;
		if (remain > 5)
			precise_usleep(1, now);
		else
			usleep(100);
	}
	return ;
}
