

#include "philo.h"

void	fork_action(t_fork *fork, t_fork_action action)
{
	if (action == TAKE)
	{
		while (true)
		{
			pthread_mutex_lock(&fork->lock);
			if (fork->taken == false)
			{
				fork->taken = true;
				pthread_mutex_unlock(&fork->lock);
				break ;
			}
			pthread_mutex_unlock(&fork->lock);
			usleep(100);
		}
	}
	else if (action == DROP)
	{
		pthread_mutex_lock(&fork->lock);
		fork->taken = false;
		pthread_mutex_unlock(&fork->lock);
	}
	return ;
}

void	philo_routine(t_rules *rules, t_philo *philo)
{
	while (continue_simulation(rules) && can_eat(philo))
	{
		fork_action(philo->first_fork, TAKE);
		print_log(philo, "has taken a fork");
		if (rules->philo_num == 1)
		{
			fork_action(philo->first_fork, DROP);
			break ;
		}
		fork_action(philo->second_fork, TAKE);
		print_log(philo, "has taken a fork");
		if (philo->first_fork->taken && philo->second_fork->taken)
			print_log(philo, "is eating");
		precise_usleep(rules->time_to_eat, get_time());
		fork_action(philo->first_fork, DROP);
		fork_action(philo->second_fork, DROP);
		print_log(philo, "is sleeping");
		precise_usleep(rules->time_to_sleep, get_time());
		if (rules->time_to_think)
		{
			print_log(philo, "is thinking");
			precise_usleep(rules->time_to_think * 0.42, get_time());
		}
	}
	return ;
}

void	*go_to_table(void *arg)
{
	t_philo	*philo;
	t_rules	*rules;

	philo = (t_philo *)arg;
	rules = philo->rules;
	pthread_mutex_lock(&rules->monitor_lock);
	philo->ready = true;
	pthread_mutex_unlock(&rules->monitor_lock);
	release_simulation(rules);
	if (rules->philo_num > 1)
	{
		if (rules->philo_num % 2 && philo->id == rules->philo_num)
			precise_usleep(rules->time_to_eat / 2, get_time());
		if (rules->philo_num % 2 == 0 && philo->id % 2 == 0)
			precise_usleep(rules->time_to_eat / 2, get_time());
	}
	philo_routine(rules, philo);
	return (NULL);
}

bool	can_eat(t_philo *philo)
{
	int	nbr_of_meals;
	int	meals_eaten;

	nbr_of_meals = philo->rules->must_eat_times;
	if (nbr_of_meals == -1)
		return (true);
	pthread_mutex_lock(&philo->meal_lock);
	meals_eaten = philo->meals_eaten;
	pthread_mutex_unlock(&philo->meal_lock);
	if (nbr_of_meals > meals_eaten)
		return (true);
	else
		return (false);
}

int	run_simulation(t_rules *rules, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < rules->philo_num)
	{
		if (pthread_create(&philos[i].thread_id, NULL, go_to_table, &philos[i]))
			return (print_error("Error > Failed creating philospher thread\n"));
		i++;
	}
	sync_simulation(rules, philos);
	if (pthread_create(&rules->monitor, NULL, monitor_philosophers, philos))
		return (print_error("Error > Failed to create monitor thread\n"));
	i = 0;
	while (i < rules->philo_num)
	{
		pthread_join(philos[i].thread_id, NULL);
		i++;
	}
	pthread_join(rules->monitor, NULL);
	destroy_mutexes(rules, philos);
	return (0);
}
