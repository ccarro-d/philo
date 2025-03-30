

# include "philo.h"

int	ft_atoi(char *str)
{
	int	sign;
	int	nbr;

	sign = 1;
	nbr = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == 43 || *str == 45)
	{
		if (*str == 45)
			sign = -1;
		str++;
	}
	while (*str)
	{
		if (*str >= 48 && *str <= 57)
			nbr = (nbr * 10) + (*str - 48);
		else
			print_error("All arguments must be numbers", 1);
		str++;
	}
	nbr *= sign;
	if (nbr < 0)
		print_error("All arguments must be positive numbers", 1);
	return (nbr);
}

void	init_args(t_args *args, char **argv)
{
	args->philo_num = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (args->philo_num == 0 || args->time_to_die == 0 || args->time_to_eat == 0 || args->time_to_sleep == 0)
		print_error("All arguments must be positive numbers", 1);
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
	{
		args.eat_repetitions = ft_atoi(argv[5]);
		if (args.eat_repetitions == 0)
			return (0);
	}
	else if (argc == 5)
		args.eat_repetitions = -1;
	else
		print_error("Invalid number of arguments", 1);
	init_args(&args, argv);
	philo(args);
	return (0);
}

/*
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
*/