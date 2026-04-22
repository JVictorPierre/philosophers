/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuth <jmuth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:24:09 by jmuth             #+#    #+#             */
/*   Updated: 2026/04/22 15:42:54 by jmuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	unlink_semaphores(void)
{
	sem_unlink("/forks");
	sem_unlink("/display");
	sem_unlink("/death_alarm");
	sem_unlink("/meal_counter");
	sem_unlink("/table");
}

static void	close_semaphores(t_table *table)
{
	sem_close(table->forks);
	sem_close(table->display);
	sem_close(table->death_alarm);
	sem_close(table->meal_counter);
	sem_close(table->table_sem);
}

void	clean_semaphores(t_table *table)
{
	close_semaphores(table);
	unlink_semaphores();
}

int	cleanup(t_table *table, int step)
{
	if (step >= 1)
		sem_close(table->forks);
	if (step >= 2)
		sem_close(table->display);
	if (step >= 3)
		sem_close(table->death_alarm);
	if (step >= 4)
		sem_close(table->meal_counter);
	unlink_semaphores();
	return (1);
}
