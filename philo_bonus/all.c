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
}#include "philo_bonus.h"

void	safe_print(philo_struct *philo, char *message)
{
	sem_wait(philo->table->display);
	printf("%zu %d %s", get_time() - philo->table->start_time,
		philo->philo_id + 1, message);
	sem_post(philo->table->display);
}#include "philo_bonus.h"

static void	close_semaphores(void)
{
	sem_unlink("/forks");
	sem_unlink("/display");
	sem_unlink("/death_alarm");
	sem_unlink("/meal_counter");
}

static void	init_semaphores(table_struct *table)
{
	close_semaphores();
	table->forks = sem_open("/forks", O_CREAT, 0644, table->nb_philo);
	table->display =  sem_open("/display", O_CREAT, 0644, 1);
	table->death_alarm = sem_open("/death_alarm", O_CREAT, 0644, 0);
	table->meal_counter = sem_open("/meal_counter", O_CREAT, 0644, 0);
}

static void	error_fork(table_struct *table, int i)
{
	close_semaphores();
	printf("Error : fork didn't work");
	i--;
	while (i >= 0)
	{
		kill(table->pids[i], SIGKILL);
		i--;
	}
}

void	global_supervisor(table_struct *table)
{
	int			i;
	pid_t		process;
	pthread_t	meal_supervisor_id;
	philo_struct	philo;

	i = 0;
	table->start_time = get_time();
	init_semaphores(table);
	while (i < table->nb_philo)
	{
		init_philo(&philo, table, i);
        process = fork();
        if (process < 0)
		{
			error_fork(table, i);
			exit (0);
		}
        if (process == 0)
        {
            philo_routine(&philo);
            exit(0);
        }
        else if (process > 0)
        {
            table->pids[i] = process;
            i++;
        }
	}
	pthread_create(&meal_supervisor_id, NULL, meal_supervisor_routine, table);
	sem_wait(table->death_alarm);
	i--;
	while (i >= 0)
	{
		kill(table->pids[i], SIGKILL);
		i--;
	}
	pthread_detach(meal_supervisor_id);
	close_semaphores();
}
#include "philo_bonus.h"

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
	table->pids = malloc(sizeof(int) * table->nb_philo);
	if (!table->pids)
		return (1);
	return (0);
}

void	init_philo(philo_struct *philo, table_struct *table, int i)
{
	philo->philo_id = i;
	philo->table = table;
	philo->last_meal = table->start_time;
	philo->eaten_meal = 0;
}#include "philo_bonus.h"

int	main(int ac, char **av)
{
	table_struct	table;

	if (ac < 5 || ac > 6)
	{
		printf("Function must have 5 or 6 arguments\n");
		return (1);
	}
	if (full_check(av) == 1)
		return (1);
	if (init_table(&table, av, ac) == 1)
    {
        printf("Error: Malloc failed\n");
        return (1);
    }
	global_supervisor(&table);
	free(table.pids);
	return (0);
}#include "philo_bonus.h"

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
}#include "philo_bonus.h"

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
}#include "philo_bonus.h"

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
#include "philo_bonus.h"

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
}#include "philo_bonus.h"

static size_t	ft_count(long n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*result;
	long	nb;

	nb = n;
	len = ft_count(nb);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	len--;
	if (nb == 0)
		result[0] = '0';
	else if (nb < 0)
	{
		result[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		result[len] = ((nb % 10) + '0');
		nb = nb / 10;
		len--;
	}
	return (result);
}

static char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	*ft_strcat(char *dest, const char *src)

{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	lens1;
	size_t	lens2;
	char	*newstr;

	if (!s1 || !s2)
		return (NULL);
	lens1 = 0;
	lens2 = 0;
	while (s1[lens1])
		lens1++;
	while (s2[lens2])
		lens2++;
	newstr = malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (!newstr)
		return (NULL);
	newstr = ft_strcpy(newstr, s1);
	newstr = ft_strcat(newstr, s2);
	return (newstr);
}
