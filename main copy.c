

# include "philo.h"

unsigned int	ft_atoi(char *str)
{
	long long	nbr;

	nbr = 0;
	if (*str == 32 || (*str >= 9 && *str <= 13) || *str == 43 || *str == 45)
    	print_error("Arguments must be positive numbers (use no signs/spaces)", 1);
	while (*str)
	{
		if (*str >= 48 && *str <= 57)
			nbr = (nbr * 10) + (*str - 48);
		else
			print_error("All arguments must be numbers", 1);
		str++;
	}
	if (nbr < 0 || nbr > UINT_MAX)
		print_error("Number out of allowed range", 1);
	return ((unsigned int)nbr);
}

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

void	print_error(char *err_msg, int err_code)
{
	printf("%s\n", err_msg);
	exit(err_code);
}

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