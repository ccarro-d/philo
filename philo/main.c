

# include "philo.h"

int	main(int argc, char **argv)
{

	t_rules rules;
	int	ret;

	if (argc != 5 && argc != 6)
		return(print_error("Invalid numer of arguments"));
	ret = init_rules(&rules, argv);
	if (ret != 0)
		return (1);
	philo(rules);
	return (0);
}

/*
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
*/