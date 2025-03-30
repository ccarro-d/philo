

#ifndef PHILO_H
# define PHILO_LONG_H

# include "./printf/ft_printf.h"
# include <errno.h>   // Para códigos de error
# include <stdbool.h> // Para usar el tipo bool
# include <stddef.h>  // Para usar size_t

// Structures
typedef struct s_args
{
	int	philo_num;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eat_repetitions;
}					t_args;

// main.c function
void				free_matrix(char **matrix);
int					main(int argc, char **argv);

#endif