/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:40:44 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/08/19 18:43:20 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_rules(t_rules *rules)
{
	printf("PRINT RULES:\n");
	printf("typedef struct s_rules\n");
	printf("{\n");
	printf("	int		rules->philo_num = %d\n", rules->philo_num);
	printf("	int		rules->time_to_die = %d\n", rules->time_to_die);
	printf("	int		rules->time_to_eat = %d\n", rules->time_to_eat);
	printf("	int		rules->time_to_sleep = %d\n", rules->time_to_sleep);
	printf("	int		rules->time_to_think = %d\n", rules->time_to_think);
	printf("	int		rules->must_eat_times = %d\n", rules->must_eat_times);
	printf("	long long	rules->start_time = %lld\n", rules->start_time);
	printf("	bool		rules->simulation_on_hold = %d\n",
		rules->simulation_on_hold);
	printf("	bool		rules->end_simulation = %d\n",
		rules->end_simulation);
	printf("}	t_rules\n");
	printf("\n\n\n");
	return ;
}

void	print_philos(t_philo *philo)
{
	printf("PRINT PHILO [%d]:\n", philo->id);
	printf("typedef struct s_philo\n");
	printf("{\n");
	printf("	int		philo->id = %d\n", philo->id);
	printf("	int		philo->meals_eaten = %d\n", philo->meals_eaten);
	printf("	int		philo->full = %d\n", philo->full);
	printf("	int		philo->last_meal = %lld\n", philo->last_meal);
	printf("}	t_philo\n");
	printf("\n\n\n");
	return ;
}
