

# include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo *philo;
	t_rules	*rules;

	philo = (t_philo *)arg;
	rules = philo->rules;

	while (rules->end_simulation == false
		&& philo->meals_eaten < rules->must_eat_times)
	{
		print_log(philo, "is thinking");
		pthread_mutex_lock(philo->left_fork);
		print_log(philo, "has taken left fork"); // para debugging
		pthread_mutex_lock(philo->right_fork);
		print_log(philo, "has taken right fork"); // para debugging
		print_log(philo, "is eating");
		usleep(rules->time_to_eat * 1e3);
		philo->meals_eaten++;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		print_log(philo, "is sleeping");
		usleep(rules->time_to_sleep * 1e3);
	}
	return (NULL);
}

void all_meals_eaten(t_philo *philos)
{
	int	i;
	int completed;

	if (philos->rules->must_eat_times == -1)
		return;
	i = 0;
	completed = 0;
	while(i < philos->rules->philo_num)
	{
		if (philos[i].meals_eaten == philos->rules->must_eat_times)
			completed++;
		i++;
	}
	if (completed == i)
		philos->rules->end_simulation = true;
	return;
}

void	*monitor_philosophers(void *arg)
{
	t_philo *philos;
	t_rules	*rules;
	int i;
	long long	hunger_time;

	philos = (t_philo *)arg;
	rules = philos->rules;
	while (rules->end_simulation == false)
	{
		i = 0;
		while (i < rules->philo_num)
		{
			pthread_mutex_lock(&philos->rules->monitor_lock);
			hunger_time = get_time() - (rules->start_time + philos[i].last_meal); 
			if (hunger_time > rules->time_to_die)
				print_log(philos[i], "is dead");
			else
			{
				all_meals_eaten(philos);
				pthread_mutex_unlock(&rules->monitor_lock);
			}
			i++;
		}
		usleep(1e3);
	}
	return (NULL);
}

int	run_simulation(t_rules *rules, t_philo *philos)
{
	int	i;
	int	ret;

	i = 0;
	while (i < rules->philo_num)
	{
		ret = pthread_create(&philos[i].thread_id, NULL, philo_routine, &philos[i]);
		if (ret != 0)
			return(print_error("Error > Failed to create philospher thread"));
		usleep(100);
			i++;
	}
	ret = pthread_create(&rules->monitor, NULL, monitor_philosophers, rules);
	if (ret != 0)
		return(print_error("Error > Failed to create philospher thread"));
	i = 0;
	while (i < rules->philo_num)
	{
		pthread_join(philos[i].thread_id, NULL);
		i++;
	}
	pthread_join(rules->monitor, NULL);
	destroy_mutexes(philos);
	return (0);
}
/*
	Con números pares
		time_to_die = time_to_eat + time_to_sleep + 10			// 10 milisegundos, por ejemplo, para dar algo de margen si el número de filósofos es grande para no ralentizar la computadora
	Con números impares
		time_to_die = time_to_eat * 2 + time_to_sleep + 10		// 
*/