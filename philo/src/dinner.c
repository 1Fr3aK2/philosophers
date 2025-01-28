/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:46:44 by raamorim          #+#    #+#             */
/*   Updated: 2025/01/28 01:43:05 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	*solo_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		gettime(MILISECONDES));
	set_increase(&philo->table->table_mutex, &philo->table->threads_running);
	write_status(FIRST_FORK, philo);
	while (!simulation_finish(philo->table))
		usleep(100);
	return (NULL);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		gettime(MILISECONDES));
	set_increase(&philo->table->table_mutex, &philo->table->threads_running);
	de_synchronize(philo);
	while (!simulation_finish(philo->table))
	{
		if (philo->full)
			break ;
		eat(philo);
		sleeping(philo);
		thinking(philo, false);
	}
	return (NULL);
}

bool	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->nbr_limits_meals == 0)
		return (false);
	else if (table->philo_nbr == 1)
		safe_thread_handle(&table->philos[0].thread_id, solo_philo,
			&table->philos[0], CREATE);
	else
	{
		while (++i < table->philo_nbr)
			safe_thread_handle(&table->philos[i].thread_id, dinner_simulation,
				&table->philos[i], CREATE);
	}
	safe_thread_handle(&table->main_thread, monitor_dinner, table, CREATE);
	table->start_simulation = gettime(MILISECONDES);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->philo_nbr)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->table_mutex, &table->end_simulation, true);
	safe_thread_handle(&table->main_thread, NULL, NULL, JOIN);
	return (true);
}
