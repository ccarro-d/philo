

# include "philo.h"

int	main(int argc, char **argv)
{
	t_rules	rules;
	t_philo	*philos;

	if (argc != 5 && argc != 6)
		return (print_error("Invalid numer of arguments"));
	if (init_rules(&rules, argv))
		return (1);
	philos = malloc(sizeof(t_philo) * rules.philo_num);
	if (!philos)
	{
		free(&rules.forks);
		return (print_error("Error > Philos allocation failed"));
	}
	if (init_philos(philos, &rules))
	{
		combined_free(&rules.forks, philos);
		return (1);
	}
	if (run_simulation(&rules, philos))
	{
		combined_free(&rules.forks, philos);
		return (1);
	}
	combined_free(&rules.forks, philos);
	return (0);
}

/*
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
*/