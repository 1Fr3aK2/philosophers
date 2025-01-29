/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:47:00 by raamorim          #+#    #+#             */
/*   Updated: 2025/01/29 03:06:34 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	sleeping(t_philo *philo)
{
	write_status(SLEEPING, philo);
	my_usleep(philo->table, philo->table->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	long	time_to_think;

	write_status(THINKING, philo);
	time_to_think = (philo->table->time_to_die - (gettime(MICROSECONDS)
				- philo->last_meal_time) - philo->table->time_to_eat) / 2;
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	my_usleep(philo->table, time_to_think);
}

void	eat(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(FIRST_FORK, philo);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(SECOND_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		gettime(MILISECONDES));
	philo->meals_counter++;
	write_status(EATING, philo);
	my_usleep(philo->table, philo->table->time_to_eat);
	if (philo->table->nbr_limits_meals > 0
		&& philo->meals_counter == philo->table->nbr_limits_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}
