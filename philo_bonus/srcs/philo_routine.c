/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuth <jmuth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:24:30 by jmuth             #+#    #+#             */
/*   Updated: 2026/04/22 15:58:44 by jmuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	clean_child_exit(t_philo *philo)
{
	sem_close(philo->sem_last_meal);
	sem_close(philo->table->forks);
	sem_close(philo->table->display);
	sem_close(philo->table->death_alarm);
	sem_close(philo->table->meal_counter);
	sem_close(philo->table->table_sem);
	free(philo->table->pids);
	exit(0);
}

static void	philo_loop_routine(t_philo *philo)
{
	sem_wait(philo->table->table_sem);
	sem_wait(philo->table->forks);
	safe_print(philo, "has taken a fork\n");
	sem_wait(philo->table->forks);
	safe_print(philo, "has taken a fork\n");
	sem_wait(philo->sem_last_meal);
	philo->last_meal = get_time();
	sem_post(philo->sem_last_meal);
	safe_print(philo, "is eating\n");
	ft_sleep(philo->table->time_to_eat);
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
	sem_post(philo->table->table_sem);
	philo->eaten_meal++;
	if (philo->table->max_meal != -1
		&& philo->eaten_meal == philo->table->max_meal)
	{
		sem_post(philo->table->meal_counter);
		clean_child_exit(philo);
	}
	safe_print(philo, "is sleeping\n");
	ft_sleep(philo->table->time_to_sleep);
	safe_print(philo, "is thinking\n");
	if (philo->table->think_time > 0)
		ft_sleep(philo->table->think_time);
}

void	*philo_routine(void *arg)
{
	char		*id;
	char		*name;
	pthread_t	time_supervision;
	t_philo		*philo;

	philo = (t_philo *)arg;
	id = ft_itoa(philo->philo_id);
	name = ft_strjoin("/meal_", id);
	philo->sem_last_meal = sem_open(name, O_CREAT, 0644, 1);
	sem_unlink(name);
	free(id);
	free(name);
	pthread_create(&time_supervision, NULL, time_supervisor_routine, philo);
	pthread_detach(time_supervision);
	if (philo->philo_id % 2 == 0)
		ft_sleep(philo->table->time_to_eat / 10);
	while (1)
	{
		philo_loop_routine(philo);
	}
	return (NULL);
}
