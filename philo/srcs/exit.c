#include "philo.h"

void	free_all(table_struct *table, philo_struct *philo)
{
	free_table(table);
	free(philo);
}
void	free_table(table_struct *table)
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
