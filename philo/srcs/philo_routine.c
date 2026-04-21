#include "philo.h"

static void	meal_routine(philo_struct *philo)
{
	pthread_mutex_lock(&philo->table->last_meal_mutex);
	philo->table->last_meal[philo->philo_id] = get_time();
	pthread_mutex_unlock(&philo->table->last_meal_mutex);
	safe_print(philo, "is eating\n");
	ft_sleep(philo->table->time_to_eat);
}

static void philo_loop_routine_action(philo_struct *philo, int first_fork, int second_fork)
{
	pthread_mutex_lock(&philo->table->forks[first_fork]);
	safe_print(philo, "has taken a fork\n");
	if (philo->table->nb_philo == 1)
	{
		ft_sleep(philo->table->time_to_die);
		pthread_mutex_unlock(&philo->table->forks[first_fork]);
		return ;
	}
	pthread_mutex_lock(&philo->table->forks[second_fork]);
	safe_print(philo, "has taken a fork\n");
	meal_routine(philo);
	pthread_mutex_unlock(&philo->table->forks[first_fork]);
	pthread_mutex_unlock(&philo->table->forks[second_fork]);
	pthread_mutex_lock(&philo->eaten_meal_mutex);
	philo->eaten_meal++;
	pthread_mutex_unlock(&philo->eaten_meal_mutex);
	safe_print(philo, "is sleeping\n");
	ft_sleep(philo->table->time_to_sleep);
	safe_print(philo, "is thinking\n");
}

void	*philo_routine(void *arg)
{
	philo_struct	*philo;
	int				left_fork;
	int				right_fork;

	philo = (philo_struct *)arg;
	left_fork = philo->philo_id;
	right_fork = (philo->philo_id + 1) % philo->table->nb_philo;
	if (philo->philo_id % 2 == 0)
		ft_sleep(philo->table->time_to_eat / 2);
	while (read_end_meal(philo->table) == 0)
	{
		if (philo->philo_id % 2 == 0)
			philo_loop_routine_action(philo, left_fork, right_fork);
		else
			philo_loop_routine_action(philo, right_fork, left_fork);
	}
	return (NULL);
}
