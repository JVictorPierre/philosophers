#include "philo.h"

int	read_end_meal(table_struct *table)
{
	int	tmp_end_meal;

	pthread_mutex_lock(&table->end_meal_mutex);
	tmp_end_meal = table->end_meal;
	pthread_mutex_unlock(&table->end_meal_mutex);
	return (tmp_end_meal);
}

long	long_atoi(char *str)
{
	long int	nb;
	int			i;

	nb = 0;
	i = 0;
	if (str[0] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10 + str[i] - '0');
		i++;
	}
	return (nb);
}

void	safe_print(philo_struct *philo, char *message)
{
	pthread_mutex_lock(&philo->table->display_mutex);
	if (read_end_meal(philo->table) == 1)
	{
		pthread_mutex_unlock(&philo->table->display_mutex);
		return ;
	}
	printf("%zu %d %s", get_time() - philo->table->start_time,
		philo->philo_id + 1, message);
	pthread_mutex_unlock(&philo->table->display_mutex);
}
