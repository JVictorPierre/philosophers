#include "philo_bonus.h"

void	*meal_supervisor_routine(void *arg)
{
	int	i;
	table_struct *table;
	
	i = 0;
	table = (table_struct *)arg;
	while (i < table->nb_philo)
	{
		sem_wait(table->meal_counter);
		i++;
	}
	sem_post(table->death_alarm);
	return (NULL);
}