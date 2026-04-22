/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 11:39:01 by jmuth             #+#    #+#             */
/*   Updated: 2026/04/22 11:39:02 by jmuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_if_only_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
	{
		printf("Argument can't be empty\n");
		return (1);
	}
	if (str[0] == '+')
		i++;
	if (str[i] == '\0')
	{
		printf("Argument must contain a valid value\n");
		return (1);
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			printf("Arguments must be positive numbers only\n");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_each_argument(char *str)
{
	long	number;

	number = long_atoi(str);
	if (number < 1 || number > INT_MAX)
	{
		printf("Error, argument value must be between 1 and INT MAX\n");
		return (1);
	}
	return (0);
}

int	full_check(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (check_if_only_digit(av[i]) == 1)
			return (1);
		if (check_each_argument(av[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}
