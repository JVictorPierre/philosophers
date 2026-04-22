/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuth <jmuth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:24:57 by jmuth             #+#    #+#             */
/*   Updated: 2026/04/22 14:26:47 by jmuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5 || ac > 6)
	{
		printf("Function must have 5 or 6 arguments\n");
		return (1);
	}
	if (full_check(av) == 1)
		return (1);
	if (init_table(&table, av, ac) == 1)
	{
		printf("Error: Malloc failed\n");
		return (1);
	}
	global_supervisor(&table);
	free(table.pids);
	return (0);
}
