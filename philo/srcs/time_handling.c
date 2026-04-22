#include "philo.h"

size_t	get_time(void)
{
	struct timeval	tv;
	size_t			ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}

void	ft_sleep(size_t timetowait, table_struct *table)
{
	size_t	endtime;

	endtime = get_time() + timetowait;
	while (get_time() < endtime)
	{
		if (read_end_meal(table) == 1)
			return ;
		usleep(NAP_TIME);
	}
}