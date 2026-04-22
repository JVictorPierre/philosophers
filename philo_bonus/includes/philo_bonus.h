/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuth <jmuth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:23:40 by jmuth             #+#    #+#             */
/*   Updated: 2026/04/22 15:43:01 by jmuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <fcntl.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>
# include <semaphore.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/wait.h>

# define NAP_TIME	500

typedef struct t_struct
{
	size_t	start_time;
	int		nb_philo;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	int		max_meal;
	sem_t	*forks;
	sem_t	*display;
	sem_t	*death_alarm;
	sem_t	*meal_counter;
	sem_t	*table_sem;
	int		*pids;
	long	think_time;
}	t_table;

typedef struct p_struct
{
	t_table			*table;
	int				philo_id;
	int				eaten_meal;
	size_t			last_meal;
	sem_t			*sem_last_meal;
}	t_philo;

char	*ft_itoa(int n);
char	*ft_strjoin(char const *s1, char const *s2);
void	*meal_supervisor_routine(void *arg);
void	*philo_routine(void *arg);
int		full_check(char **av);
void	*time_supervisor_routine(void *arg);
int		init_table(t_table *table, char **av, int ac);
void	global_supervisor(t_table *table);
long	long_atoi(char *str);
size_t	get_time(void);
void	safe_print(t_philo *philo, char *message);
void	ft_sleep(size_t timetowait);
void	init_philo(t_philo *philo, t_table *table, int i);
void	clean_semaphores(t_table *table);
void	unlink_semaphores(void);
int		init_semaphores(t_table *table);
int		cleanup(t_table *table, int step);

#endif
