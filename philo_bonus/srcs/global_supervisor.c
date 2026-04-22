/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_supervisor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuth <jmuth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:32:29 by jmuth             #+#    #+#             */
/*   Updated: 2026/04/22 16:00:31 by jmuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	error_fork(t_table *table, int i)
{
	clean_semaphores(table);
	printf("Error : fork didn't work");
	i--;
	while (i >= 0)
	{
		kill(table->pids[i], SIGKILL);
		i--;
	}
}

static void	supervisor_loop(t_table *table, t_philo *philo, int *i)
{
	pid_t		process;

	init_philo(philo, table, *i);
	process = fork();
	if (process < 0)
	{
		error_fork(table, *i);
		free(table->pids);
		exit (1);
	}
	if (process == 0)
	{
		philo_routine(&philo);
		exit(0);
	}
	else if (process > 0)
	{
		table->pids[*i] = process;
		(*i)++;
	}
}

static void	kill_child(t_table *table, int i)
{
	while (i >= 0)
	{
		kill(table->pids[i], SIGKILL);
		i--;
	}
	i = 0;
	while (i < table->nb_philo)
	{
		waitpid(table->pids[i], NULL, 0);
		i++;
	}
}

void	global_supervisor(t_table *table)
{
	int			i;
	pthread_t	meal_supervisor_id;
	t_philo		philo;

	i = 0;
	table->start_time = get_time();
	if (init_semaphores(table) == 1)
	{
		printf("Error: couldn't open semaphores");
		exit (1);
	}
	while (i < table->nb_philo)
	{
		supervisor_loop(table, &philo, &i);
	}
	pthread_create(&meal_supervisor_id, NULL, meal_supervisor_routine, table);
	sem_wait(table->death_alarm);
	kill_child(table, i - 1);
	pthread_detach(meal_supervisor_id);
	clean_semaphores(table);
}
