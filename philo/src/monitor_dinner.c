/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_dinner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:46:58 by raamorim          #+#    #+#             */
/*   Updated: 2025/01/28 06:06:34 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	died(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = gettime(MILISECONDES) - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	time_to_die = philo->table->time_to_die / 1e3;
	if (elapsed > time_to_die)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (!all_running(&table->table_mutex, &table->threads_running,
			table->philo_nbr))
		;
	while (!simulation_finish(table))
	{
		i = -1;
		while (++i < table->philo_nbr && !simulation_finish(table))
		{
			if (died(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->end_simulation, true);
				write_status(DIED, table->philos + i);
			}
		}
	}
	return (NULL);
}
