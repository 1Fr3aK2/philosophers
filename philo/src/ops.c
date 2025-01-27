/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:47:00 by raamorim          #+#    #+#             */
/*   Updated: 2025/01/27 13:47:01 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	sleeping(t_philo *philo)
{
	write_status(SLEEPING, philo);
	my_usleep(philo->table->time_to_sleep, philo->table);
}

void	thinking(t_philo *philo, bool simulation)
{
	long	time_eat;
	long	time_sleep;
	long	time_think;

	if (!simulation)
		write_status(THINKING, philo);
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	time_eat = philo->table->time_to_eat;
	time_sleep = philo->table->time_to_sleep;
	time_think = time_eat * 2 - time_sleep;
	if (time_think < 0)
		time_think = 0;
	my_usleep(time_think * 0.5, philo->table);
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
	my_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limits_meals > 0
		&& philo->meals_counter == philo->table->nbr_limits_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}
