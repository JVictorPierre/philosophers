#include "philo.h"

static void	end_meal(philo_struct *philo)
{
	pthread_mutex_lock(&philo->table->end_meal_mutex);
	philo->table->end_meal = 1;
	pthread_mutex_unlock(&philo->table->end_meal_mutex);
}

static void	philo_death(philo_struct *philo)
{
	pthread_mutex_lock(&philo->table->display_mutex);
	pthread_mutex_lock(&philo->table->end_meal_mutex);
	philo->table->end_meal = 1;
	pthread_mutex_unlock(&philo->table->end_meal_mutex);
	printf("%zu %d died\n", get_time() - philo->table->start_time,
		philo->philo_id + 1);
	pthread_mutex_unlock(&philo->table->display_mutex);
}

static void	check_meal(philo_struct *philo, int *philo_satiates)
{
	pthread_mutex_lock(&philo->eaten_meal_mutex);
	if (philo->table->max_meal != -1 && philo->eaten_meal >= philo->table->max_meal)
		*philo_satiates += 1;
	pthread_mutex_unlock(&philo->eaten_meal_mutex);
	if (*philo_satiates == philo->table->nb_philo)
		end_meal(philo);
}
static size_t get_last_meal(table_struct *table, int i)
{
	size_t			last_meal_tmp;

	pthread_mutex_lock(&table->last_meal_mutex);
	last_meal_tmp = table->last_meal[i];
	pthread_mutex_unlock(&table->last_meal_mutex);
	return (last_meal_tmp);
}

void	supervisor_routine(philo_struct *philo)
{
	int				i;
	int				philo_satiates;
	size_t			last_meal_tmp;
	table_struct	*table;

	i = 0;
	table = philo[0].table;
	while (read_end_meal(table) == 0)
	{
		philo_satiates = 0;
		while (i < table->nb_philo)
		{
			last_meal_tmp = get_last_meal(table, i);
			if (get_time() > last_meal_tmp + table->time_to_die)
			{
				philo_death(&philo[i]);
				return ;
			}
			check_meal(&philo[i], &philo_satiates);
			i++;
		}
		usleep(50);
		i = 0;
	}
}
