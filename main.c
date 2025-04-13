

# include "philo.h"

int	main(int argc, char **argv)
{

	t_args args;

	if (argc == 6)
		args.must_eat_times = ft_atoi(argv[5]);
	else if (argc == 5)
		args.must_eat_times = -1;
	else
		print_error("Invalid number of arguments", 1);
	init_args(&args, argv);
	philo(args);
	return (0);
}

/*
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
*/