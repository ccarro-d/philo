

# include "philo.h"

int	init_philos(t_philo *philos, t_rules *rules)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (i < rules->philo_num)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].full = false;
		philos[i].last_meal = rules->start_time;
		philos[i].left_fork = &rules->forks[i];
		philos[i].right_fork = &rules->forks[(i + 1) % rules->philo_num];
		ret = pthread_mutex_init(&philos->meal_lock, NULL);
		if (ret != 0)
			return (print_error("Error > Print lock initialization failed"));
		philos[i].rules = rules;
		i++;
	}
	return (0);
}

int	init_mutexes(t_rules *rules)
{
	int	i;
	int	ret;

	rules->forks = malloc(sizeof(t_rules) * rules->philo_num);
	if (!rules->forks)
		return(print_error("Error > Forks allocation failed"));
	i = 0;
	while (i < rules->philo_num)
	{
		ret = pthread_mutex_init(&rules->forks[i], NULL);
		if (ret != 0)
			return(print_error("Error > Forks initialization failed"));
		i++;
	}
	ret = pthread_mutex_init(&rules->print_locks, NULL);
	if (ret != 0)
		return(print_error("Error > Print lock initialization failed"));
	ret = pthread_mutex_init(&rules->monitor_lock, NULL);
	if (ret != 0)
		return(print_error("Error > Monitor lock initialization failed"));
	return (0);
}

int	check_rules(t_rules *rules)
{
	if (rules->philo_num == 0)
		return(print_error("philo_num must be a positive number"));
	else if (rules->philo_num > 200)
		return(print_error("philo_num must not exceed '200'"));
	else if (rules->time_to_die < 60)
		return(print_error("time_to_die must be at least 60ms"));
	else if (rules->time_to_eat < 60)
		return(print_error("time_to_eat must be at least 60ms"));
	else if (rules->time_to_sleep < 60)
		return(print_error("time_to_sleep be at least 60ms"));
	else if (rules->must_eat_times == 0)
		return(printf("Specified must_eat_times = 0 | END OF SIMULATION"));
	else if (rules->time_to_die > INT_MAX
		|| rules->time_to_eat > INT_MAX
		|| rules->time_to_sleep > INT_MAX
		|| rules->must_eat_times > INT_MAX)
		return(print_error("No argument should be bigger than INT_MAX"));
	else
		return (0);
	// return (0);
}

int	init_rules(t_rules *rules, char **argv)
{
	int	ret;

	rules->philo_num = ft_atoi(argv[1], "philo_num", 1);
	rules->time_to_die = ft_atoi(argv[2], "time_to_die", 2);
	rules->time_to_eat = ft_atoi(argv[3], "time_to_eat", 3);
	rules->time_to_sleep = ft_atoi(argv[4], "time_to_sleep", 4);
	if (rules->philo_num == -1 || rules->time_to_die == -1
		|| rules->time_to_eat == -1 ||rules->time_to_sleep == -1)
		return (1);
	if (argv[5])
	{
		rules->must_eat_times = ft_atoi(argv[5], "must_eat_times", 5);
		if (rules->must_eat_times == -1)
			return (1);
	}
	else
		rules->must_eat_times == -1;
	rules->start_time  = get_time();
	rules->end_simulation = false;
	ret = check_rules(rules);
	if (ret != 0)
		return (ret);
	ret = init_mutexes(rules);
		if (ret != 0)
			return (ret);
	return (0);
}
