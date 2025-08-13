

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (n)
	{
		if (*str1 > *str2)
			return (1);
		if (*str1 < *str2)
			return (-1);
		if (*str1 == '\0' || *str2 == '\0')
			break ;
		str1++;
		str2++;
		n--;
	}
	return (0);
}

void	print_log(t_philo *philo, char *message)
{
	long long	timestamp;
	bool		is_dead;
	bool		is_eating;

	is_dead = (ft_strncmp(message, "died", ft_strlen(message)) == 0);
	is_eating = (ft_strncmp(message, "is eating", ft_strlen(message)) == 0);
	pthread_mutex_lock(&philo->rules->print_locks);
	if (continue_simulation(philo->rules) || !ft_strncmp(message, "died", 4))
	{
		timestamp = get_time();
		if (is_eating)
		{
			pthread_mutex_lock(&philo->meal_lock);
			philo->meals_eaten++;
			philo->last_meal = timestamp;
			pthread_mutex_unlock(&philo->meal_lock);
		}
		pthread_mutex_lock(&philo->rules->monitor_lock);
		if (is_dead)
			philo->rules->end_simulation = true;
		timestamp -= philo->rules->start_time;
		pthread_mutex_unlock(&philo->rules->monitor_lock);
		printf("%lld %d %s\n", timestamp, philo->id, message);
	}
	pthread_mutex_unlock(&philo->rules->print_locks);
}

int	ft_atoi(char *str, char *rule, int arg_nbr)
{
	long long	nbr;

	nbr = 0;
	if (*str == 32 || (*str >= 9 && *str <= 13) || *str == 43 || *str == 45)
	{
		printf("ERROR > Argument %d (%s): used signs/spaces\n", arg_nbr, rule);
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
	if (err_msg)
	{
		write(2, err_msg, ft_strlen(err_msg));
		write(2, "\n", 1);
	}
	return (1);
}
