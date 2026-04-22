/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuth <jmuth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 11:38:45 by jmuth             #+#    #+#             */
/*   Updated: 2026/04/22 11:50:29 by jmuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	read_end_meal(t_table *table)
{
	int	tmp_end_meal;

	pthread_mutex_lock(&table->end_meal_mutex);
	tmp_end_meal = table->end_meal;
	pthread_mutex_unlock(&table->end_meal_mutex);
	return (tmp_end_meal);
}

long	long_atoi(char *str)
{
	long int	nb;
	int			i;

	nb = 0;
	i = 0;
	if (str[0] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10 + str[i] - '0');
		i++;
	}
	return (nb);
}

void	safe_print(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->table->display_mutex);
	if (read_end_meal(philo->table) == 1)
	{
		pthread_mutex_unlock(&philo->table->display_mutex);
		return ;
	}
	printf("%zu %d %s", get_time() - philo->table->start_time,
		philo->philo_id + 1, message);
	pthread_mutex_unlock(&philo->table->display_mutex);
}
