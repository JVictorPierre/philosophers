/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal_supervisor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuth <jmuth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:24:25 by jmuth             #+#    #+#             */
/*   Updated: 2026/04/22 14:31:25 by jmuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*meal_supervisor_routine(void *arg)
{
	int		i;
	t_table	*table;

	i = 0;
	table = (t_table *)arg;
	while (i < table->nb_philo)
	{
		sem_wait(table->meal_counter);
		i++;
	}
	sem_post(table->death_alarm);
	return (NULL);
}
