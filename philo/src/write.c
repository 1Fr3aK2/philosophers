/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:47:17 by raamorim          #+#    #+#             */
/*   Updated: 2025/01/28 04:34:34 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	write_status(t_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = gettime(MILISECONDES) - philo->table->start_simulation;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if ((status == FIRST_FORK || status == SECOND_FORK)
		&& !simulation_finish(philo->table))
		printf("%ld %d has taken a fork\n", elapsed, philo->id);
	else if (status == SLEEPING && !simulation_finish(philo->table))
		printf("%ld %d is sleeping\n", elapsed, philo->id);
	else if (status == THINKING && !simulation_finish(philo->table))
		printf("%ld %d is thinking\n", elapsed, philo->id);
	else if (status == DIED)
		printf("%ld %d died\n", elapsed, philo->id);
	else if (status == EATING && !simulation_finish(philo->table))
		printf("%ld %d is eating\n", elapsed, philo->id);
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}
