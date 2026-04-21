#include "philo_bonus.h"

void	safe_print(philo_struct *philo, char *message)
{
	sem_wait(philo->table->display);
	printf("%zu %d %s", get_time() - philo->table->start_time,
		philo->philo_id + 1, message);
	sem_post(philo->table->display);
}