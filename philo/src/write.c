#include "philosophers.h"

void	write_status(t_status status, t_philos *philo)
{
	long time_passed;

	time_passed = gettime(MILISECONDES) - philo->table->start_simulation;
	mutex_handle(&philo->table->write_mutex, LOCK);
	if (philo->full)
		return ;
    if (!simulation_finish(philo->table))
	{
		if (status == FIRST_FORK || status == SECOND_FORK)
			printf("%ld: %d has taken a fork\n", time_passed, philo->id);
		else if (status == SLEEPING)
			printf("%ld: %d is sleeping\n", time_passed, philo->id);
		else if (status == THINKING)
			printf("%ld: %d is thinking\n", time_passed, philo->id);
		else if (status == DIED)
			printf("%ld: %d died\n", time_passed, philo->id);
		else if (status == EATING)
			printf("%ld: %d is eating\n", time_passed, philo->id);
	}
	mutex_handle(&philo->table->write_mutex, UNLOCK);
}