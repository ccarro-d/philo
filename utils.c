

# include "philo.h"

unsigned int	ft_atoi(char *str)
{
	long long	nbr;

	nbr = 0;
	if (*str == 32 || (*str >= 9 && *str <= 13) || *str == 43 || *str == 45)
    	print_error("Args must be positive numbers (use no signs/spaces)", 1);
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

void	print_error(char *err_msg, int err_code)
{
	printf("%s\n", err_msg);
	exit(err_code);
}
