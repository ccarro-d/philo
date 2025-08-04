

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;
	long long		ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
	// "1000LL" Asegura que la multiplicación sea en long long
	return (ms);
}

void	print_log(t_philo *philo, char *message)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->rules->print_locks);
	if (philo->rules->end_simulation == false)
	{
		timestamp = get_time() - philo->rules->start_time;
		if (message == "is eating")
		{
			pthread_mutex_lock(&philo->meal_lock);
			philo->eating = true;
			philo->meals_eaten++;
			philo->last_meal = timestamp;
			pthread_mutex_unlock(&philo->meal_lock);
		}
		if (message == "is dead")
		{
			pthread_mutex_lock(&philo->rules->monitor_lock);
			philo->rules->end_simulation = true;
			pthread_mutex_unlock(&philo->rules->monitor_lock);
		}
		printf("%lld   %d   %s\n", timestamp, philo->id, message);
	}
	pthread_mutex_unlock(&philo->rules->print_locks);
	return ;
}

int	ft_atoi(char *str, char *rule, int arg_nbr)
{
	long long	nbr;

	nbr = 0;
	if (*str == 32 || (*str >= 9 && *str <= 13) || *str == 43 || *str == 45)
	{
		printf("ERROR > Argument %d (%s): used signs/spaces\n)", arg_nbr, rule);
		return (-1);
	}
	while (*str)
	{
		if (*str >= 48 && *str <= 57)
			nbr = (nbr * 10) + (*str - 48);
		else
		{
			printf("ERROR > Argument %d (%s) is not a number\n", arg_nbr, rule);
			return (-1);
		}
		str++;
	}
	if (nbr < 0 || nbr > INT_MAX)
	{
		printf("ERROR > Argument %d (%s): is out of range\n", arg_nbr, rule);
		return (-1);
	}
	return ((int)nbr);
}

int	print_error(char *err_msg)
{
	printf("%s\n", err_msg);
	return (1);
}

void	combined_free(pthread_mutex_t *forks, t_philo *philos)
{
	free(forks);
	free(philos);
	return ;
}
