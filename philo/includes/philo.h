/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuth <jmuth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 11:41:59 by jmuth             #+#    #+#             */
/*   Updated: 2026/04/22 11:51:07 by jmuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	size_t				start_time;
	int					nb_philo;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	pthread_mutex_t		*forks;
	size_t				*last_meal;
	pthread_mutex_t		display_mutex;
	pthread_mutex_t		last_meal_mutex;
	pthread_mutex_t		end_meal_mutex;
	int					end_meal;
	int					max_meal;
	long				think_time;
}	t_table;

typedef struct p_struct
{
	pthread_t		thread_id;
	t_table			*table;
	int				philo_id;
	int				eaten_meal;
	pthread_mutex_t	eaten_meal_mutex;
}	t_philo;

int		init_table(t_table *table, char **av, int ac);
long	long_atoi(char *str);
void	init_philo(t_philo *philo, t_table *table, int i);
void	*philo_routine(void *arg);
size_t	get_time(void);
void	ft_sleep(size_t timetowait, t_table *table);
void	supervisor_routine(t_philo *philo);
void	free_table(t_table *table);
void	free_all(t_table *table, t_philo *philo);
int		read_end_meal(t_table *table);
int		full_check(char **av);
void	safe_print(t_philo *philo, char *message);

#endif
