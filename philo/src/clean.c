/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:39:30 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/08/19 18:43:11 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	free_forks(t_fork *forks, int init_forks, char *err_msg)
{
	int	i;

	i = 0;
	while (i < init_forks)
	{
		pthread_mutex_destroy(&forks[i].lock);
		i++;
	}
	free (forks);
	return (print_error(err_msg));
}

void	destroy_mutexes(t_rules *rules, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < rules->philo_num)
	{
		pthread_mutex_destroy(&rules->forks[i].lock);
		pthread_mutex_destroy(&philos[i].meal_lock);
		i++;
	}
	pthread_mutex_destroy(&rules->print_locks);
	pthread_mutex_destroy(&rules->monitor_lock);
	return ;
}

void	combined_free(t_fork *forks, t_philo *philos)
{
	free(forks);
	free(philos);
	return ;
}

int	destroy_and_free(t_rules *rules, t_philo *philos)
{
	destroy_mutexes(rules, philos);
	free(rules->forks);
	free(philos);
	return (1);
}
