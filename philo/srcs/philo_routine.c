/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuth <jmuth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 11:38:15 by jmuth             #+#    #+#             */
/*   Updated: 2026/04/22 11:55:56 by jmuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	meal_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->last_meal_mutex);
	philo->table->last_meal[philo->philo_id] = get_time();
	pthread_mutex_unlock(&philo->table->last_meal_mutex);
	safe_print(philo, "is eating\n");
	ft_sleep(philo->table->time_to_eat, philo->table);
}

static void	philo_loop_routine_action(t_philo *philo, int fork1, int fork2)
{
	pthread_mutex_lock(&philo->table->forks[fork1]);
	safe_print(philo, "has taken a fork\n");
	if (philo->table->nb_philo == 1)
	{
		ft_sleep(philo->table->time_to_die, philo->table);
		pthread_mutex_unlock(&philo->table->forks[fork1]);
		return ;
	}
	pthread_mutex_lock(&philo->table->forks[fork2]);
	safe_print(philo, "has taken a fork\n");
	meal_routine(philo);
	pthread_mutex_unlock(&philo->table->forks[fork1]);
	pthread_mutex_unlock(&philo->table->forks[fork2]);
	pthread_mutex_lock(&philo->eaten_meal_mutex);
	philo->eaten_meal++;
	pthread_mutex_unlock(&philo->eaten_meal_mutex);
	safe_print(philo, "is sleeping\n");
	ft_sleep(philo->table->time_to_sleep, philo->table);
	safe_print(philo, "is thinking\n");
	if (philo->table->think_time > 0)
		ft_sleep(philo->table->think_time, philo->table);
}

void	*philo_routine(void *arg)
{
	t_philo			*philo;
	int				left_fork;
	int				right_fork;

	philo = (t_philo *)arg;
	left_fork = philo->philo_id;
	right_fork = (philo->philo_id + 1) % philo->table->nb_philo;
	if (philo->philo_id % 2 == 0)
		ft_sleep(philo->table->time_to_eat / 10, philo->table);
	while (read_end_meal(philo->table) == 0)
	{
		if (philo->philo_id % 2 == 0)
			philo_loop_routine_action(philo, left_fork, right_fork);
		else
			philo_loop_routine_action(philo, right_fork, left_fork);
	}
	return (NULL);
}
