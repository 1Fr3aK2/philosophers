#include "philosophers.h"

static void assign_forks(t_philos *philo, t_fork *forks, int pos)
{
	if (philo->table->number % 2 == 0)
	{
		philo->first_fork = &forks[pos];
		philo->second_fork = &forks[(pos + 1) % philo->table->number];
	}
	else
	{
		philo->first_fork = &forks[(pos + 1) % philo->table->number];
		philo->second_fork = &forks[pos];
	}
}


static void init_philo(t_table *table)
{
	int	i;
	t_philos *philo;

	i = 0;
	while (i < table->number)
	{
		philo = &table->philos[i]; //
		philo->id = i + 1;
		philo->meals_counter = 0;
		philo->last_meal_time = 0;
		philo->table = table;
		philo->second_fork = NULL;
		philo->first_fork = NULL;
		mutex_handle(&philo->philo_mutex, INIT);
		assign_forks(philo, table->forks, i);
		i++;
	}
}

void	struct_init(t_table *table)
{
	int	i;

	if (!table)
		return ;
	table->end_simulation = false;
	table->ready = false;
	table->philos = malloc(sizeof(t_philos) * table->number);
	if (!table->philos)
	{
    	exit_msg("Falha ao alocar memória para os filósofos.");
    	return;
	}
	mutex_handle(&table->table_mutex, INIT);
	table->forks = malloc(sizeof(t_fork) * table->number);
	if (!table->forks)
	{
    	free(table->philos); // Libera memória previamente alocada
    	exit_msg("Falha ao alocar memória para os garfos.");
    	return;
	}
	i = 0;
	while(i < table->number)
	{
		mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
		i++;
	}
	init_philo(table);
}