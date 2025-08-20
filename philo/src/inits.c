/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:40:37 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/08/20 04:12:25 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_philos(t_philo *philos, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->philo_num)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = 0;
		philos[i].ready = false;
		philos[i].full = false;
		philos[i].first_fork = &rules->forks[i];
		if (rules->philo_num > 1)
			philos[i].second_fork = &rules->forks[(i + 1) % rules->philo_num];
		if (i % 2)
		{
			philos[i].first_fork = &rules->forks[(i + 1) % rules->philo_num];
			philos[i].second_fork = &rules->forks[i];
		}
		if (pthread_mutex_init(&philos[i].meal_lock, NULL))
			return (print_error("Error > Meal lock initialization failed"));
		philos[i].rules = rules;
		i++;
	}
	return (0);
}

int	init_mutexes(t_rules *rules)
{
	int	i;

	rules->forks = malloc(sizeof(t_fork) * rules->philo_num);
	if (!rules->forks)
		return (print_error("Error > Forks allocation failed"));
	i = 0;
	while (i < rules->philo_num)
	{
		rules->forks[i].taken = false;
		if (pthread_mutex_init(&rules->forks[i].lock, NULL))
			return (free_forks(rules->forks, i, "Error > Forks init failed"));
		i++;
	}
	if (pthread_mutex_init(&rules->print_locks, NULL))
		return (free_forks(rules->forks, i, "Error > PrintLock init failed"));
	if (pthread_mutex_init(&rules->monitor_lock, NULL))
	{
		pthread_mutex_destroy(&rules->print_locks);
		return (free_forks(rules->forks, i, "Error > MonitLock init failed"));
	}
	return (0);
}

int	check_rules(t_rules *rules)
{
	if (rules->philo_num == 0)
		return (print_error("philo_num must be a positive number"));
	else if (rules->philo_num > 200)
		return (print_error("philo_num must not exceed '200'"));
	else if (rules->time_to_die < 60)
		return (print_error("time_to_die must be at least 60ms"));
	else if (rules->time_to_eat < 60)
		return (print_error("time_to_eat must be at least 60ms"));
	else if (rules->time_to_sleep < 60)
		return (print_error("time_to_sleep must be at least 60ms"));
	return (0);
}

void	thinking_time(t_rules *rules)
{
	long long	ttd;
	long long	tte;
	long long	tts;
	long long	ttt;
	long long	margin;

	ttd = rules->time_to_die;
	tte = rules->time_to_eat;
	tts = rules->time_to_sleep;
	if (rules->philo_num <= 1 || (rules->philo_num % 2 == 0 && tte <= tts))
		ttt = 0;
	else
	{
		ttt = tte - tts;
		margin = ttd - tte - tts;
		if (rules->philo_num % 2)
			ttt += 1;
		if (margin < ttt)
			ttt = margin;
		if (ttt < 0)
			ttt = 0;
	}
	rules->time_to_think = ttt;
}

int	init_rules(t_rules *rules, char **argv)
{
	rules->philo_num = ft_atoi(argv[1], "philo_num", 1);
	if (rules->philo_num == 0)
		return (print_error("philo_num must be a positive number"));
	rules->time_to_die = ft_atoi(argv[2], "time_to_die", 2);
	rules->time_to_eat = ft_atoi(argv[3], "time_to_eat", 3);
	rules->time_to_sleep = ft_atoi(argv[4], "time_to_sleep", 4);
	if (rules->philo_num == -1 || rules->time_to_die == -1
		|| rules->time_to_eat == -1 || rules->time_to_sleep == -1)
		return (1);
	if (argv[5])
	{
		rules->must_eat_times = ft_atoi(argv[5], "must_eat_times", 5);
		if (rules->must_eat_times == -1)
			return (1);
	}
	else
		rules->must_eat_times = -1;
	rules->simulation_on_hold = true;
	rules->end_simulation = false;
	if (check_rules(rules))
		return (1);
	thinking_time(rules);
	if (init_mutexes(rules))
		return (1);
	return (0);
}
