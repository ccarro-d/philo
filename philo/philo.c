

# include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;

	while (philo->rules->end_simulation == false)
	{
		print_log(philo, "is thinking");
		pthread_mutex_lock(philo->left_fork);
		print_log(philo, "has taken left fork"); // para debugging
		pthread_mutex_lock(philo->right_fork);
		print_log(philo, "has taken right fork"); // para debugging
		print_log(philo, "is eating");
		usleep(philo->rules->time_to_eat * 1e3);
		philo->meals_eaten++;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		print_log(philo, "is sleeping");
	}
	return (NULL);
}
void	*monitor_routine(void *arg)
{
	void(*arg);
	return;
}

int	start_simulation(t_rules *rules, t_philo *philos)
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
	ret = pthread_create(&rules->monitor, NULL, monitor_routine, rules);
	if (ret != 0)
		 return(print_error("Error > Failed to create philospher thread"));

	// ¿Tendría sentido poner el start_time aquí?

	i = 0;
	while (i < rules->philo_num)
	{
		pthread_join(philos[i].thread_id, NULL);
		i++;
	}
	// Si llegamos aquí, es que todos los filósofos están llenos y la simulación debe terminar
	return (0);
}
/*
	Con números pares
		time_to_die = time_to_eat + time_to_sleep + 10			// 10 milisegundos, por ejemplo, para dar algo de margen si el número de filósofos es grande para no ralentizar la computadora
	Con números impares
		time_to_die = time_to_eat * 2 + time_to_sleep + 10		// 
*/