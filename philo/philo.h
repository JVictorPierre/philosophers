#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>

# define NAP_TIME	500

typedef struct t_struct
{
	size_t	start_time;
	int	nb_philo;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	pthread_mutex_t		*forks;
	size_t	*last_meal;
	pthread_mutex_t		display_mutex;
	pthread_mutex_t		last_meal_mutex;
	pthread_mutex_t		end_meal_mutex;
	int		end_meal;
	int		max_meal;
} table_struct;

typedef struct p_struct
{
	pthread_t		thread_id;
	table_struct	*table;
	int				philo_id;
	int				eaten_meal;
	pthread_mutex_t	eaten_meal_mutex;
} philo_struct;

int		init_table(table_struct *table, char **av, int ac);
long	long_atoi(char *str);
void	init_philo(philo_struct *philo, table_struct *table, int i);
void	*philo_routine(void *arg);
size_t	get_time(void);
void	ft_sleep(size_t timetowait);
void	supervisor_routine(philo_struct *philo);
void	free_table(table_struct *table);
void	free_all(table_struct *table, philo_struct *philo);
int	read_end_meal(table_struct *table);
int	full_check(char **av);
void	safe_print(philo_struct *philo, char *message);

#endif