

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>	// Para hilos y mutexes
# include <stdlib.h>	// Para malloc, free, exit
# include <stdio.h>		// Para printf
# include <unistd.h>	// Para usleep
# include <sys/time.h>	// Para gettimeofday
# include <stdbool.h>	// Para usar el tipo bool
# include <limits.h>	// Para MAX/MIN por tipo de dato

// Typedefs

typedef struct s_fork
{
	bool			taken;
	pthread_mutex_t	lock;
}	t_fork;

typedef enum s_fork_action
{
	TAKE,
	DROP
}	t_fork_action;

typedef struct s_rules
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				must_eat_times;
	long long		start_time;
	bool			simulation_on_hold;
	bool			end_simulation;
	t_fork			*forks;
	pthread_mutex_t	print_locks;
	pthread_t		monitor;
	pthread_mutex_t	monitor_lock;
}	t_rules;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	bool			ready;
	bool			full;
	long long		last_meal;
	pthread_t		thread_id;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_mutex_t	meal_lock;
	t_rules			*rules;
}	t_philo;

// main.c functions
int			main(int argc, char **argv);

// utils.c functions
int			print_error(char *err_msg);
int			ft_atoi(char *str, char *rule, int arg_nbr);
void		print_log(t_philo *philo, char *message);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

// inits.c functions
int			init_rules(t_rules *rules, char **argv);
int			check_rules(t_rules *rules);
void		thinking_time(t_rules *rules);
int			init_mutexes(t_rules *rules);
int			init_philos(t_philo *philos, t_rules *rules);

// philo.c funcitions
int			run_simulation(t_rules *rules, t_philo *philos);
bool		can_eat(t_philo *philo);
void		philo_routine(t_rules *rules, t_philo *philo);
void		*go_to_table(void *arg);

// monitor.c funcitions
void		sync_simulation(t_rules *rules, t_philo *philos);
void		release_simulation(t_rules	*rules);
bool		continue_simulation(t_rules	*rules);
void		all_meals_eaten(t_philo *philos);
void		*monitor_philosophers(void *arg);

// clean.c funcitions
int			free_forks(t_fork *forks, int init_forks, char *err_msg);
void		destroy_mutexes(t_rules *rules, t_philo *philos);
void		combined_free(t_fork *forks, t_philo *philos);
int			destroy_and_free(t_rules *rules, t_philo *philos);

// time.c functions
long long	get_time(void);
void		precise_usleep(long long time_ms, long long start);

// debug.c functions
void		print_rules(t_rules *rules);
void		print_philos(t_philo *philo);

#endif