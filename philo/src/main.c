/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:40:32 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/08/19 18:45:57 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_rules	rules;
	t_philo	*philos;

	if (argc == 1)
		return (print_error("Arguments missing"));
	if (argc != 5 && argc != 6)
		return (print_error("Invalid number of arguments"));
	if (init_rules(&rules, argv))
		return (1);
	philos = malloc(sizeof(t_philo) * rules.philo_num);
	if (!philos)
	{
		free(rules.forks);
		return (print_error("Error > Philos allocation failed"));
	}
	if (init_philos(philos, &rules))
		return (destroy_and_free(&rules, philos));
	if (run_simulation(&rules, philos))
		return (destroy_and_free(&rules, philos));
	combined_free(rules.forks, philos);
	return (0);
}
