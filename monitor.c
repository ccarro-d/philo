

#include "philo.h"

bool	continue_simulation(t_rules	*rules)
{
	bool	to_be_continued;

	to_be_continued = true;
	if (rules->simulation_on_hold)
		return (to_be_continued);
	pthread_mutex_lock(&rules->monitor_lock);
	if (rules->end_simulation)
		to_be_continued = false;
	pthread_mutex_unlock(&rules->monitor_lock);
	return (to_be_continued);
}

void	all_meals_eaten(t_philo *philos)
{
	int	i;
	int	completed;
	int	meals_eaten;

	if (philos->rules->must_eat_times == -1)
		return ;
	i = 0;
	completed = 0;
	while (i < philos->rules->philo_num)
	{
		pthread_mutex_lock(&philos[i].meal_lock);
		meals_eaten = philos[i].meals_eaten;
		pthread_mutex_unlock(&philos[i].meal_lock);
		if (meals_eaten >= philos->rules->must_eat_times)
			completed++;
		i++;
	}
	if (completed == philos->rules->philo_num)
	{
		pthread_mutex_lock(&philos->rules->monitor_lock);
		philos->rules->end_simulation = true;
		pthread_mutex_unlock(&philos->rules->monitor_lock);
	}
	return ;
}

void	*monitor_philosophers(void *arg)
{
	t_philo		*philos;
	t_rules		*rules;
	int			i;
	long long	hunger_time;

	philos = (t_philo *)arg;
	rules = philos->rules;
	while (continue_simulation(rules))
	{
		i = -1;
		while (++i < rules->philo_num)
		{
			pthread_mutex_lock(&philos[i].meal_lock);
			hunger_time = get_time() - philos[i].last_meal;
			pthread_mutex_unlock(&philos[i].meal_lock);
			if (hunger_time > rules->time_to_die)
				print_log(&philos[i], "died");
			else
				all_meals_eaten(philos);
		}
		precise_usleep(1, get_time());
	}
	return (NULL);
}
