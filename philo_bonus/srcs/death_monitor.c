#include "philo_bonus.h"

void static	philo_death(philo_struct *philo)
{
	sem_wait(philo->table->display);
	printf("%zu %d died\n", get_time() - philo->table->start_time,
		philo->philo_id + 1);
	sem_post(philo->table->death_alarm);
}

void	*time_supervisor_routine(void *arg)
{
	philo_struct	*philo;
	size_t			last_meal_tmp;
	
	philo = (philo_struct *)arg;
	while (1)
	{
		sem_wait(philo->sem_last_meal);
		last_meal_tmp = philo->last_meal;
		sem_post(philo->sem_last_meal);
		if (get_time() > last_meal_tmp + philo->table->time_to_die)
		{
				philo_death(philo);
				return (NULL);
		}
	ft_sleep(100);
	}
	return (NULL);
}