#include "philo.h"

void	free_all(table_struct *table, philo_struct *philo)
{
	free_table(table);
	free(philo);
}
void	free_table(table_struct *table)
{
	if (table->last_meal)
		free(table->last_meal);
	pthread_mutex_destroy(&table->display_mutex);
	pthread_mutex_destroy(&table->last_meal_mutex);
	pthread_mutex_destroy(&table->end_meal_mutex);
}#include "philo.h"
static void	init_pthreads_table(table_struct	*table)
{
	int	i;

	i = 0;
	pthread_mutex_init(&table->display_mutex, NULL);
	pthread_mutex_init(&table->last_meal_mutex, NULL);
	pthread_mutex_init(&table->end_meal_mutex, NULL);
	while (i != table->nb_philo)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
}

int	init_table(table_struct *table, char **av, int ac)
{
	memset(table, 0, sizeof(table_struct));
	if (ac == 5)
		table->max_meal = -1;
	else if (ac == 6)
		table->max_meal = long_atoi(av[5]);
	table->nb_philo = long_atoi(av[1]);
	table->time_to_die = long_atoi(av[2]);
	table->time_to_eat = long_atoi(av[3]);
	table->time_to_sleep = long_atoi(av[4]);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	table->last_meal = malloc(sizeof(size_t) * table->nb_philo);
	if (!table->forks || !table->last_meal)
	{
		free_table(table);
		return (1);
	}
	init_pthreads_table(table);
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
	while (i != table->nb_philo)
	{
	pthread_join(philo[i].thread_id, NULL);
	pthread_mutex_destroy(&table->forks[i]);
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
	table.start_time = get_time();
	init_philo_loop(&table, philo);
	create_threads(&table, philo);
	supervisor_routine(philo);
	clean_threads(&table, philo);
	free_all(&table, philo);
	return (0);
}
#include "philo.h"

static int	check_if_only_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
	{
		printf("Argument can't be empty\n");
		return (1);
	}
	if (str[0] == '+')
		i++;
	if (str[i] == '\0')
	{
		printf("Argument must contain a valid value\n");
		return (1);
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			printf("Arguments must be positive numbers only\n");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_each_argument(char *str)
{
	long	number;

	number = long_atoi(str);
	if (number < 1 || number > INT_MAX)
	{
		printf("Error, argument value must be between 1 and INT MAX\n");
		return (1);
	}
	return (0);
}

int	full_check(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (check_if_only_digit(av[i]) == 1)
			return (1);
		if (check_each_argument(av[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}#include "philo.h"

static void	meal_routine(philo_struct *philo)
{
	pthread_mutex_lock(&philo->table->last_meal_mutex);
	philo->table->last_meal[philo->philo_id] = get_time();
	pthread_mutex_unlock(&philo->table->last_meal_mutex);
	safe_print(philo, "is eating\n");
	ft_sleep(philo->table->time_to_eat);
}

static void	philo_loop_routine_odd(philo_struct *philo)
{
	int				left_fork;
	int				right_fork;

	left_fork = philo->philo_id;
	right_fork = (philo->philo_id + 1) % philo->table->nb_philo;
	pthread_mutex_lock(&philo->table->forks[right_fork]);
	safe_print(philo, "has taken a fork\n");
	if (philo->table->nb_philo == 1)
	{
		ft_sleep(philo->table->time_to_die);
		pthread_mutex_unlock(&philo->table->forks[right_fork]);
		return ;
	}
	pthread_mutex_lock(&philo->table->forks[left_fork]);
	safe_print(philo, "has taken a fork\n");
	meal_routine(philo);
	pthread_mutex_unlock(&philo->table->forks[right_fork]);
	pthread_mutex_unlock(&philo->table->forks[left_fork]);
	safe_print(philo, "is sleeping\n");
	ft_sleep(philo->table->time_to_sleep);
	safe_print(philo, "is thinking\n");
}
static void	philo_loop_routine_even(philo_struct *philo)
{
	int				left_fork;
	int				right_fork;

	left_fork = philo->philo_id;
	right_fork = (philo->philo_id + 1) % philo->table->nb_philo;
	pthread_mutex_lock(&philo->table->forks[left_fork]);
	safe_print(philo, "has taken a fork\n");
	if (philo->table->nb_philo == 1)
	{
		ft_sleep(philo->table->time_to_die);
		pthread_mutex_unlock(&philo->table->forks[left_fork]);
		return ;
	}
	pthread_mutex_lock(&philo->table->forks[right_fork]);
	safe_print(philo, "has taken a fork\n");
	meal_routine(philo);
	pthread_mutex_unlock(&philo->table->forks[left_fork]);
	pthread_mutex_unlock(&philo->table->forks[right_fork]);
	safe_print(philo, "is sleeping\n");
	ft_sleep(philo->table->time_to_sleep);
	safe_print(philo, "is thinking\n");
}

static void	philo_loop_routine(void *arg)
{
	philo_struct	*philo;
	
	philo = (philo_struct *)arg;
	if (philo->philo_id % 2 == 0)
		philo_loop_routine_even(philo);
	else
		philo_loop_routine_odd(philo);
}

void	*philo_routine(void *arg)
{
	philo_struct	*philo;

	philo = (philo_struct *)arg;
	if (philo->philo_id % 2 == 0)
		ft_sleep(philo->table->time_to_eat / 2);
	while (read_end_meal(philo->table) == 0)
	{
		philo_loop_routine(arg);
		pthread_mutex_lock(&philo->eaten_meal_mutex);
		philo->eaten_meal++;
		pthread_mutex_unlock(&philo->eaten_meal_mutex);
	}
	return (NULL);
}
#include "philo.h"

void static	end_meal(philo_struct *philo)
{
	pthread_mutex_lock(&philo->table->end_meal_mutex);
	philo->table->end_meal = 1;
	pthread_mutex_unlock(&philo->table->end_meal_mutex);
}

void static	philo_death(philo_struct *philo, int i)
{
	pthread_mutex_lock(&philo->table->display_mutex);
	pthread_mutex_lock(&philo->table->end_meal_mutex);
	philo->table->end_meal = 1;
	pthread_mutex_unlock(&philo->table->end_meal_mutex);
	printf("%zu %d died\n", get_time() - philo->table->start_time,
		philo[i].philo_id + 1);
	pthread_mutex_unlock(&philo->table->display_mutex);
}

void static	check_meal(philo_struct *philo, int *philo_satiates)
{
	pthread_mutex_lock(&philo->eaten_meal_mutex);
	if (philo->table->max_meal != -1 && philo->eaten_meal >= philo->table->max_meal)
		*philo_satiates += 1;
	if (*philo_satiates == philo->table->nb_philo)
		end_meal(philo);
	pthread_mutex_unlock(&philo->eaten_meal_mutex);
}

void	supervisor_routine(philo_struct *philo)
{
	int		i;
	int		philo_satiates;
	size_t	last_meal_tmp;

	i = 0;
	while (read_end_meal(philo->table) == 0)
	{
		philo_satiates = 0;
		while (i < philo->table->nb_philo)
		{
			pthread_mutex_lock(&philo->table->last_meal_mutex);
			last_meal_tmp = philo[i].table->last_meal[i];
			pthread_mutex_unlock(&philo->table->last_meal_mutex);
			if (get_time() > last_meal_tmp + philo->table->time_to_die)
			{
				philo_death(philo, i);
				return ;
			}
			check_meal(&philo[i], &philo_satiates);
			i++;
		}
		usleep(50);
		i = 0;
	}
}
#include "philo.h"

size_t	get_time(void)
{
	struct timeval	tv;
	size_t			ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}

void	ft_sleep(size_t timetowait)
{
	size_t	endtime;

	endtime = get_time() + timetowait;
	while (get_time() < endtime)
	{
		usleep(NAP_TIME);
	}
}#include "philo.h"

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
