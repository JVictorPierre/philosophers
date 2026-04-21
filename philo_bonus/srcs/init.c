#include "philo_bonus.h"

int	init_table(table_struct *table, char **av, int ac)
{
	memset(table, 0, sizeof(table_struct));
	if (ac == 5)
		table->max_meal = -1;
	else if (ac == 6)
		table->max_meal = long_atoi(av[5]);
	table->nb_philo = long_atoi(av[1]);
	table->time_to_die = long_atoi(av[2]);
	table->time_to_eat = long_atoi(av[3]);
	table->time_to_sleep = long_atoi(av[4]);
	table->pids = malloc(sizeof(int) * table->nb_philo);
	if (!table->pids)
		return (1);
	return (0);
}

void	init_philo(philo_struct *philo, table_struct *table, int i)
{
	philo->philo_id = i;
	philo->table = table;
	philo->last_meal = table->start_time;
	philo->eaten_meal = 0;
}