/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuth <jmuth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 11:37:58 by jmuth             #+#    #+#             */
/*   Updated: 2026/04/22 11:51:40 by jmuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_table *table, t_philo *philo)
{
	free_table(table);
	free(philo);
}

void	free_table(t_table *table)
{
	int	i;

	i = 0;
	if (table->last_meal)
		free(table->last_meal);
	if (table->forks)
	{
		while (i < table->nb_philo)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
		free(table->forks);
	}
	pthread_mutex_destroy(&table->display_mutex);
	pthread_mutex_destroy(&table->last_meal_mutex);
	pthread_mutex_destroy(&table->end_meal_mutex);
}
