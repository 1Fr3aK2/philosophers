#include "philo.h"

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
		;
}

void	de_synchronize(t_philo *philo)
{
	if (philo->table->philo_nbr % 2 == 0)
	{
		if (philo->id % 2 == 0)
			my_usleep(3e4, philo->table);
	}
	else
	{
		if (philo->id % 2 != 0)
			thinking(philo, true);
	}
}

bool	simulation_finish(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}
