#include "philosophers.h"
 
static void thinking(t_philos *philo)
{
    write_status(THINKING, philo);
}

static void sleeping(t_philos *philo)
{
    write_status(SLEEPING, philo);
    my_usleep(philo->table->time_to_sleep, philo->table);
}

 static void	eat(t_philos *philo)
{
	printf("DEBUG: Philo %d is attempting to eat.\n", philo->id);
	mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(FIRST_FORK, philo);
	mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(SECOND_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		gettime(MILISECONDES));
	philo->meals_counter++;
	write_status(EATING, philo);
	my_usleep(philo->table->time_to_eat, philo->table);
	if (philo->meals_counter == philo->table->number)
	{
		printf("DEBUG: Philo %d is now full. Meals: %d\n", philo->id, philo->meals_counter);
		set_bool(&philo->philo_mutex, &philo->full, true);
	}
	mutex_handle(&philo->first_fork->fork, UNLOCK);
	mutex_handle(&philo->second_fork->fork, UNLOCK);
}

static void	*dinner_sim(void *data)
{
	t_philos	*philo;
	philo = (t_philos *)data;
	wait_threads(philo->table);
	// enquanto a simulação nao tiver acabado
	while (!simulation_finish(philo->table))
	{
		if (philo->full)
			break ;
		eat(philo);
        sleeping(philo);
		thinking(philo);
	}
    return (NULL);
}

void	dinner_start(t_table *table)
{
	int i;

	if (!table)
		return ;
	i = 0;
	if (table->number == 0)
		return ;
	else if (table->number == 1)
		return ; // fazer
	else
	{
		while (i < table->number)
		{
			thread_handle(&table->philos[i].thread_id, dinner_sim,
				&table->philos[i], CREATE);
			printf("thread: %d\n", i);
			i++;
		}
	}
	table->start_simulation = gettime(MILISECONDES);
	// start simulation
	set_bool(&table->table_mutex, &table->ready, true);
	// simulation has started

	// WAIT
	i = -1;
	while (++i < table->number)
		thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	// todos estao cheios
}