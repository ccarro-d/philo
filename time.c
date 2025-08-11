

#include "philo.h"

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

void	sync_simulation(t_rules *rules, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < rules->philo_num)
	{
		if (philos[i].ready)
			i++;
		usleep(100);
	}
	usleep(50);
	rules->start_time = get_time();
	i = 0;
	while (i < rules->philo_num)
	{
		philos[i].last_meal = rules->start_time;
		i++;
	}
	rules->simulation_on_hold = false;
	return ;
}
