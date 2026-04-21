#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>
# include <semaphore.h>
# include <sys/types.h>
# include <signal.h>

# define NAP_TIME	500

typedef struct t_struct
{
	size_t	start_time;
	int	nb_philo;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	int		max_meal;
	sem_t	*forks;
	sem_t	*display;
	sem_t	*death_alarm;
	sem_t	*meal_counter;
	int		*pids;
} table_struct;

typedef struct p_struct
{
	table_struct	*table;
	int				philo_id;
	int				eaten_meal;
	size_t			last_meal;
	sem_t			*sem_last_meal;
} philo_struct;

char	*ft_itoa(int n);
char	*ft_strjoin(char const *s1, char const *s2);
void	*meal_supervisor_routine(void *arg);
void	*philo_routine(void *arg);
int		full_check(char **av);
void	*time_supervisor_routine(void *arg);
int		init_table(table_struct *table, char **av, int ac);
void	global_supervisor(table_struct *table);
long	long_atoi(char *str);
size_t	get_time(void);
void	safe_print(philo_struct *philo, char *message);
void	ft_sleep(size_t timetowait);
void	init_philo(philo_struct *philo, table_struct *table, int i);

#endif