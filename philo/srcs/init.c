#include "philo.h"

static void	init_table_values(table_struct *table, char **av, int ac)
{
	if (ac == 5)
		table->max_meal = -1;
	else if (ac == 6)
		table->max_meal = long_atoi(av[5]);
	table->nb_philo = long_atoi(av[1]);
	table->time_to_die = long_atoi(av[2]);
	table->time_to_eat = long_atoi(av[3]);
	table->time_to_sleep = long_atoi(av[4]);
}
static void	init_table_mutexes(table_struct	*table)
{
	pthread_mutex_init(&table->display_mutex, NULL);
	pthread_mutex_init(&table->last_meal_mutex, NULL);
	pthread_mutex_init(&table->end_meal_mutex, NULL);
}

static void	init_fork_mutexes(table_struct	*table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
}

int	init_table(table_struct *table, char **av, int ac)
{
	memset(table, 0, sizeof(table_struct));
	init_table_values(table, av, ac);
	init_table_mutexes(table);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if (!table->forks)
	{
		free_table(table);
		return (1);
	}
	init_fork_mutexes(table);
	table->last_meal = malloc(sizeof(size_t) * table->nb_philo);
	if (!table->last_meal)
	{
		free_table(table);
		return (1);
	}
	return (0);
}

void	init_philo(philo_struct *philo, table_struct *table, int i)
{
	philo->philo_id = i;
	philo->table = table;
	philo->table->last_meal[i] = table->start_time;
	philo->eaten_meal = 0;
	pthread_mutex_init(&philo->eaten_meal_mutex, NULL);
}