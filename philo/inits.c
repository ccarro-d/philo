

# include "philo.h"

int	check_rules(t_rules *rules)
{
	if (rules->philo_num == 0)
		return(print_error("philo_num must be a positive number"));
	else if (rules->philo_num > 200)
		return(print_error("philo_num must not exceed '200'"));
	else if (rules->time_to_die == 0)
		return(print_error("time_to_die must be a positive number"));
	else if (rules->time_to_eat == 0)
		return(print_error("time_to_eat must be a positive number"));
	else if (rules->time_to_sleep == 0)
		return(print_error("time_to_sleep must be a positive number"));
	else if (rules->must_eat_times == 0)
		return(printf("Specified must_eat_times = 0 | END OF SIMULATION"));
	else if (rules->time_to_die > INT_MAX || rules->time_to_eat > INT_MAX || rules->time_to_sleep > INT_MAX || rules->must_eat_times > INT_MAX)
		return(print_error("No argument should be bigger than INT_MAX"));
	else
		return (0);
	// return (0);
}

int	init_rules(t_rules *rules, char **argv)
{
	int	check;

	rules->philo_num = ft_atoi(argv[1], "philo_num", 1);
	rules->time_to_die = ft_atoi(argv[2], "time_to_die", 2);
	rules->time_to_eat = ft_atoi(argv[3], "time_to_eat", 3);
	rules->time_to_sleep = ft_atoi(argv[4], "time_to_sleep", 4);
	if (rules->philo_num == -1 || rules->time_to_die == -1 || rules->time_to_eat == -1 || rules->time_to_sleep == -1)
		return (1);
	if (argv[5])
	{
		rules->must_eat_times = ft_atoi(argv[5], "must_eat_times", 5);
		if (rules->must_eat_times == -1)
			return (1);
	}
	else
		rules->must_eat_times == -1;
	rules->start_time = gettime();
	rules->anyone_dead = false;
	check = check_rules(rules);
	if (check != 0)
		return (check);
	return (0);
}
