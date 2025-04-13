

# include "philo.h"

void	init_args(t_args *args, char **argv)
{
	args->philo_num = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (args->philo_num == 0)
		print_error("philo_num must be a positive number", 1);
	else if (args->philo_num > 200)
		print_error("philo_num must not exceed '200'", 1);
	else if (args->time_to_die == 0)
		print_error("time_to_die must be a positive number", 1);
	else if (args->time_to_eat == 0)
		print_error("time_to_eat must be a positive number", 1);
	else if (args->time_to_sleep == 0)
		print_error("time_to_sleep must be a positive number", 1);
	else if (args->must_eat_times == 0)
	{
		printf("Specified must_eat_times = 0 | END OF SIMULATION");
		return (0);
	}
	else
		return;
}
