#include "../includes/philo.h"

void	error_exit(const char *error)
{
	printf("%s\n", error);
}

void	my_usleep(long t_microseconds, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = gettime(MIRCOSECONDS);
	while (gettime(MIRCOSECONDS) - start < t_microseconds)
	{
		if (simulation_finish(table))
			break ;
		elapsed = gettime(MIRCOSECONDS) - start;
		rem = t_microseconds - elapsed;
		if (rem > 1e3)
			usleep(rem / 2);
		else
		{
			while (gettime(MIRCOSECONDS) - start < t_microseconds)
				;
		}
	}
}

long	gettime(t_time time)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Gettimeofday failed");
	if (time == SECONDS)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (time == MILISECONDES)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (time == MIRCOSECONDS)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_exit("Wrong input\n");
	return (1);
}

void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		if (&philo->philo_mutex)
			safe_mutex_handle(&philo->philo_mutex, DESTROY);
	}
	if (&table->write_mutex)
		safe_mutex_handle(&table->write_mutex, DESTROY);
	if (&table->table_mutex)
		safe_mutex_handle(&table->table_mutex, DESTROY);
	if (table->forks)
		free(table->forks);
	if (table->philos)
		free(table->philos);
}

bool	all_running(t_mtx *mutex, long *threads, long nbr)
{
	bool	ret;

	ret = false;
	safe_mutex_handle(mutex, LOCK);
	if (*threads == nbr)
		ret = true;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}
