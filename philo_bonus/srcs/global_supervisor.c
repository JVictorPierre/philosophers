#include "philo_bonus.h"

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
