/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:40:28 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/08/20 03:51:15 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	sync_simulation(t_rules *rules, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < rules->philo_num)
	{
		pthread_mutex_lock(&rules->monitor_lock);
		if (philos[i].ready)
			i++;
		pthread_mutex_unlock(&rules->monitor_lock);
		usleep(100);
	}
	usleep(50);
	pthread_mutex_lock(&rules->monitor_lock);
	rules->start_time = get_time();
	pthread_mutex_unlock(&rules->monitor_lock);
	i = 0;
	while (i < rules->philo_num)
	{
		philos[i].last_meal = rules->start_time;
		i++;
	}
	pthread_mutex_lock(&rules->monitor_lock);
	rules->simulation_on_hold = false;
	pthread_mutex_unlock(&rules->monitor_lock);
	return ;
}

void	release_simulation(t_rules	*rules)
{
	while (true)
	{
		pthread_mutex_lock(&rules->monitor_lock);
		if (rules->simulation_on_hold == false)
		{
			pthread_mutex_unlock(&rules->monitor_lock);
			break ;
		}
		pthread_mutex_unlock(&rules->monitor_lock);
		usleep(100);
	}
}

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

	if (philos->rules->must_eat_times == -1)
		return ;
	i = 0;
	completed = 0;
	while (i < philos->rules->philo_num)
	{
		pthread_mutex_lock(&philos[i].meal_lock);
		if (!philos[i].full
			&& (philos[i].meals_eaten >= philos->rules->must_eat_times))
			philos[i].full = true;
		if (philos[i].full == true)
			completed++;
		pthread_mutex_unlock(&philos[i].meal_lock);
		i++;
	}
	if (completed == philos->rules->philo_num)
	{
		pthread_mutex_lock(&philos->rules->monitor_lock);
		philos->rules->end_simulation = true;
		pthread_mutex_unlock(&philos->rules->monitor_lock);
	}
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
			{
				print_log(&philos[i], "died");
				break ;
			}
		}
		all_meals_eaten(philos);
		precise_usleep(1 / 2, get_time());
	}
	return (NULL);
}
