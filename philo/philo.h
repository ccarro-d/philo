

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
# include <stdint.h>	// Para el tipo de dato uint64_t (es un tipo de dato entero sin signo de 64 bits, ideal para almacenar grandes cantidades de datos sin la necesidad de representar valores negativos, como por ejemplo, identificadores de objetos, contadores, o fechas)

// Structures
typedef struct s_rules
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_times;

	long long		start_time;
	bool			end_simulation;

	pthread_mutex_t	*forks;
	pthread_mutex_t	print_locks;

	pthread_t		monitor; 
	pthread_mutex_t	monitor_lock;
	
}	t_rules;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	bool			full;
	long long		last_meal;
	//char			status;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_lock;
	t_rules			*rules;
}	t_philo;

// Es una estructura que se utiliza en diversas funciones de C para manejar el tiempo, como select, gettimeofday, y settimeofday
/*	typedef struct timeval
{
	long tv_sec;	// Un valor entero que representa el número de segundos
	long tv_usec;	// Un valor entero que representa el número de microsegundos (un millón de partes de un segundo)
}	TIMEVAL; */

// main.c functions
int			main(int argc, char **argv);

// utils.c functions
int			print_error(char *err_msg);
int			ft_atoi(char *str, char *rule, int arg_nbr);

// inits.c functions
int			init_rules(t_rules *rules, char **argv);

// philo.c funcitions

// monitor.c funcitions

// clean.c funcitions

#endif