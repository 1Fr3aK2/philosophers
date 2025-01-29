/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:47:15 by raamorim          #+#    #+#             */
/*   Updated: 2025/01/29 02:55:32 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	error_exit(const char *error)
{
	printf("%s\n", error);
	return ;
}

void	my_usleep(t_table *table, long sleep_time)
{
	long	wake_up;

	wake_up = gettime(MICROSECONDS) + sleep_time;
	while (gettime(MICROSECONDS) < wake_up)
	{
		if (simulation_finish(table))
			break ;
		usleep(100);
	}
}

long	gettime(t_time time)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	if (time == SECONDS)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (time == MILISECONDES)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (time == MICROSECONDS)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		return (-1);
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
		safe_mutex_handle(&philo->philo_mutex, DESTROY);
	}
	safe_mutex_handle(&table->write_mutex, DESTROY);
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
