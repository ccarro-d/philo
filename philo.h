

#ifndef PHILO_H
# define PHILO_LONG_H

# include "./printf/ft_printf.h"
# include <errno.h>   // Para códigos de error
# include <stdbool.h> // Para usar el tipo bool
# include <stddef.h>  // Para usar size_t

// Structures
typedef struct s_args
{
	unsigned int	philo_num;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	must_eat_times;
}					t_args;

// main.c function
int				main(int argc, char **argv);
void			print_error(char *err_msg, int err_code);
unsigned int	ft_atoi(char *str);
void			init_args(t_args *args, char **argv);

#endif