/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuth <jmuth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:24:18 by jmuth             #+#    #+#             */
/*   Updated: 2026/04/22 15:52:55 by jmuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_table(t_table *table, char **av, int ac)
{
	memset(table, 0, sizeof(t_table));
	if (ac == 5)
		table->max_meal = -1;
	else if (ac == 6)
		table->max_meal = long_atoi(av[5]);
	table->nb_philo = long_atoi(av[1]);
	table->time_to_die = long_atoi(av[2]);
	table->time_to_eat = long_atoi(av[3]);
	table->time_to_sleep = long_atoi(av[4]);
	table->pids = malloc(sizeof(int) * table->nb_philo);
	table->think_time = (((long)table->time_to_die
				- (long)table->time_to_eat
				- (long)table->time_to_sleep) / 2);
	if (!table->pids)
		return (1);
	return (0);
}

void	init_philo(t_philo *philo, t_table *table, int i)
{
	philo->philo_id = i;
	philo->table = table;
	philo->last_meal = table->start_time;
	philo->eaten_meal = 0;
}

static int	open_one_sem(sem_t **sem, char *name, int value)
{
	*sem = sem_open(name, O_CREAT, 0644, value);
	if (*sem == SEM_FAILED)
		return (1);
	return (0);
}

int	init_semaphores(t_table *table)
{
	int	slots;

	unlink_semaphores();
	if (open_one_sem(&table->forks, "/forks", table->nb_philo) == 1)
		return (cleanup(table, 0));
	if (open_one_sem(&table->display, "/display", 1) == 1)
		return (cleanup(table, 1));
	if (open_one_sem(&table->death_alarm, "/death_alarm", 0) == 1)
		return (cleanup(table, 2));
	if (open_one_sem(&table->meal_counter, "/meal_counter", 0) == 1)
		return (cleanup(table, 3));
	if (table->nb_philo > 1)
		slots = table->nb_philo / 2;
	else
		slots = 1;
	if (open_one_sem(&table->table_sem, "/table", slots) == 1)
		return (cleanup(table, 4));
	return (0);
}
