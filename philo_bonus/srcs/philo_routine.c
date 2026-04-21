#include "philo_bonus.h"

void	*philo_routine(void *arg)
{
	char			*id;
	char			*name;
	pthread_t		time_supervision;
	philo_struct	*philo;

	philo = (philo_struct *)arg;
	id = ft_itoa(philo->philo_id);
	name = ft_strjoin("/meal_", id);
	philo->sem_last_meal = sem_open(name, O_CREAT, 0644, 1);
	sem_unlink(name);
	free(id);
	free(name);
	pthread_create(&time_supervision, NULL, time_supervisor_routine, philo);
	if (philo->philo_id % 2 == 0)
		ft_sleep(philo->table->time_to_eat / 2);
	while (1)
	{
		sem_wait(philo->table->forks);
		sem_wait(philo->table->forks);
		safe_print(philo, "is eating\n");
		sem_wait(philo->sem_last_meal);
		philo->last_meal = get_time();
		sem_post(philo->sem_last_meal);
		ft_sleep(philo->table->time_to_eat);
		sem_post(philo->table->forks);
		sem_post(philo->table->forks);
		philo->eaten_meal++;
		if (philo->table->max_meal != -1 && philo->eaten_meal == philo->table->max_meal)
		{
			sem_post(philo->table->meal_counter);
			exit (0);
		}
		safe_print(philo, "is sleeping\n");
		ft_sleep(philo->table->time_to_sleep);
		safe_print(philo, "is thinking\n");
	}
}
