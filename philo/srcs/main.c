#include "philo.h"

static void	init_philo_loop(table_struct *table, philo_struct *philo)
{
	int	i;
	
	i = 0;
	while (i != table->nb_philo)
	{
		init_philo(&philo[i], table, i);
		i++;
	}
}
static void	create_threads(table_struct *table, philo_struct *philo)
{
	int	i;

	i = 0;
	while (i != table->nb_philo)	
	{
		pthread_create(&philo[i].thread_id, NULL, philo_routine, &philo[i]);
		i++;
	}
}

static void	clean_threads(table_struct *table, philo_struct *philo)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
	pthread_join(philo[i].thread_id, NULL);
	pthread_mutex_destroy(&philo[i].eaten_meal_mutex);
	i++;
	}
	
}

int	main(int ac, char **av)
{
	table_struct	table;
	philo_struct	*philo;

	if (ac < 5 || ac > 6)
	{
		printf("Function must have 5 or 6 arguments\n");
		return (1);
	}
	if (full_check(av) == 1)
		return (1);
	if (init_table(&table, av, ac) == 1)
		return (1);
	philo = malloc(sizeof(philo_struct) * table.nb_philo);
	if (!philo)
	{
		free_table(&table);
		return (1);
	}
	table.start_time = get_time();
	init_philo_loop(&table, philo);
	create_threads(&table, philo);
	supervisor_routine(philo);
	clean_threads(&table, philo);
	free_all(&table, philo);
	return (0);
}
