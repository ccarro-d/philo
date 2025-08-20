/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:40:14 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/08/20 20:48:24 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
	{
		write (fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write (fd, "-", 1);
		n *= -1;
	}
	if (0 <= n && n <= 9)
	{
		n += 48;
		write (fd, &n, 1);
	}
	else
	{
		ft_putnbr_fd(n / 10, fd);
		c = n % 10 + 48;
		write (fd, &c, 1);
	}
}

void	ft_putstr_fd(char *txt, int fd)
{
	if (txt)
		write(fd, txt, ft_strlen(txt));
}

int	print_error_atoi(int arg_nbr, char *rule, char *error_message)
{
	ft_putstr_fd("ERROR > Argument ", 2);
	ft_putnbr_fd(arg_nbr, 2);
	ft_putstr_fd(" (", 2);
	ft_putstr_fd(rule, 2);
	ft_putstr_fd("): ", 2);
	ft_putstr_fd(error_message, 2);
	write(2, "\n", 1);
	return (-1);
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
