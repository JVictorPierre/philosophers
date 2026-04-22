/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:25:13 by jmuth             #+#    #+#             */
/*   Updated: 2026/04/22 14:25:14 by jmuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	get_time(void)
{
	struct timeval	tv;
	size_t			ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}

void	ft_sleep(size_t timetowait)
{
	size_t	endtime;

	endtime = get_time() + timetowait;
	while (get_time() < endtime)
	{
		usleep(NAP_TIME);
	}
}
