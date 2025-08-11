

#include "philo.h"

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
