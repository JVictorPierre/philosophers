/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuth <jmuth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:24:01 by jmuth             #+#    #+#             */
/*   Updated: 2026/04/22 14:30:02 by jmuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void static	philo_death(t_philo *philo)
{
	sem_wait(philo->table->display);
	printf("%zu %d died\n", get_time() - philo->table->start_time,
		philo->philo_id + 1);
	sem_post(philo->table->death_alarm);
}

void	*time_supervisor_routine(void *arg)
{
	t_philo	*philo;
	size_t	last_meal_tmp;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->sem_last_meal);
		last_meal_tmp = philo->last_meal;
		sem_post(philo->sem_last_meal);
		if (get_time() > last_meal_tmp + philo->table->time_to_die)
		{
			philo_death(philo);
			return (NULL);
		}
		usleep(50);
	}
	return (NULL);
}
