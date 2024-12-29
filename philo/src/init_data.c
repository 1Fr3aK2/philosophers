#include "philosophers.h"

static void init_philo(t_table *table)
{
	int	i;
	i = 0;
	while(i < table->number)
	{
		table->philos->id = i + 1;
		table->philos->meals_counter = 0;
		table->philos->last_meal_time = 0;
		table->philos->table = table;
		table->philos->left_fork = NULL;
		table->philos->right_fork = NULL;
		
		i++;
	}
}



void	struct_init(t_table *table)
{
	int	i;

	if (!table)
		return ;
	table->end_simulation = false;
	table->philos = malloc(sizeof(t_philos) * table->number);
	if (!table->philos)
		return ;
	table->forks = malloc(sizeof(t_fork) * table->number);
	if (!table->forks)
		return ;
	i = 0;
	while(i < table->number)
	{
		mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
		i++;
	}
	init_philo(table);
}