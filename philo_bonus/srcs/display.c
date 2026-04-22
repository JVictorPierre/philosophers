/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:24:43 by jmuth             #+#    #+#             */
/*   Updated: 2026/04/22 14:24:45 by jmuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	safe_print(t_philo *philo, char *message)
{
	sem_wait(philo->table->display);
	printf("%zu %d %s", get_time() - philo->table->start_time,
		philo->philo_id + 1, message);
	sem_post(philo->table->display);
}
