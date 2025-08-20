/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:40:24 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/08/20 20:00:32 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	fork_action(t_rules *rules, t_fork *fork, t_fork_action action)
{
	if (action == DROP && continue_simulation(rules))
	{
		pthread_mutex_lock(&fork->lock);
		fork->taken = false;
		pthread_mutex_unlock(&fork->lock);
		return (1);
	}
	while (continue_simulation(rules))
	{
		pthread_mutex_lock(&fork->lock);
		if (fork->taken == false)
		{
			fork->taken = true;
			pthread_mutex_unlock(&fork->lock);
			return (1);
		}
		pthread_mutex_unlock(&fork->lock);
		usleep(100);
	}
	return (0);
}

void	philo_routine(t_rules *rules, t_philo *philo)
{
	while (continue_simulation(rules))
	{
		if (!fork_action(rules, philo->first_fork, TAKE))
			break ;
		print_log(philo, "has taken a fork");
		if (rules->philo_num == 1)
		{
			fork_action(rules, philo->first_fork, DROP);
			break ;
		}
		if (!fork_action(rules, philo->second_fork, TAKE))
			break ;
		print_log(philo, "has taken a fork");
		print_log(philo, "is eating");
		watcher_usleep(rules, rules->time_to_eat, get_time());
		fork_action(rules, philo->first_fork, DROP);
		fork_action(rules, philo->second_fork, DROP);
		print_log(philo, "is sleeping");
		watcher_usleep(rules, rules->time_to_sleep, get_time());
		if (rules->time_to_think)
		{
			print_log(philo, "is thinking");
			watcher_usleep(rules, rules->time_to_think, get_time());
		}
	}
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
	if (philo->id % 2 == 0)
		watcher_usleep(rules, rules->time_to_eat / 2, get_time());
	philo_routine(rules, philo);
	return (NULL);
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
