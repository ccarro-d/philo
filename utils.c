

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

	pthread_mutex_lock(&philo->rules->print_locks);
	if (philo->rules->end_simulation == false)
	{
		timestamp = get_time();
		if (!ft_strncmp(message, "is eating", ft_strlen(message)))
		{
			pthread_mutex_lock(&philo->meal_lock);
			philo->meals_eaten++;
			philo->last_meal = timestamp;
			pthread_mutex_unlock(&philo->meal_lock);
		}
		if (!ft_strncmp(message, "died", ft_strlen(message)))
		{
			pthread_mutex_lock(&philo->rules->monitor_lock);
			philo->rules->end_simulation = true;
			pthread_mutex_unlock(&philo->rules->monitor_lock);
		}
		timestamp -= philo->rules->start_time;
		printf("%lld %d %s\n", timestamp, philo->id, message);
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
		printf("%s\n", err_msg);
	return (1);
}
