

#ifndef PHILO_H
# define PHILO_H

//# include "./printf/ft_printf.h"
# include <pthread.h>	// Para hilos y mutexes
# include <stdlib.h>	// Para malloc, free, exit
# include <stdio.h>		// Para printf
# include <unistd.h>	// Para usleep
# include <sys/time.h>	// Para gettimeofday
# include <errno.h>		// Para códigos de error
# include <stdbool.h>	// Para usar el tipo bool
# include <limits.h>	// Para MAX/MIN por tipo de dato

// Structures
typedef struct s_args
{
	unsigned int	philo_num;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	must_eat_times;

	bool			anyone_dead;
	long long		start_time;

	
}					t_args;

typedef struct s_philo
{
	xxx	
}					t_philo;

// main.c functions
int				main(int argc, char **argv);

// utils.c functions
void			print_error(char *err_msg, int err_code);
unsigned int	ft_atoi(char *str);

// inits.c functions
void			init_args(t_args *args, char **argv);

// philo.c funcitions

#endif