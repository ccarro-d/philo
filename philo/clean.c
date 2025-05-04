

# include "philo.h"

void destroy_mutexes(t_philo *philos)
{
	int	i;
	t_rules *rules;
	
	i = 0;
	rules = philos->rules;
	while (i < rules->philo_num)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&rules->monitor_lock);
	pthread_mutex_destroy(&rules->print_locks);
	return;
}
