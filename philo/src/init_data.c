#include "philosophers.h"

void	struct_init(t_table *table)
{
	if (!table)
		return ;
	table->end_simulation = false;
	table->philos = malloc(sizeof(t_philos) * table->number);
	if (!table->philos)
		return ;
	table->forks = malloc(sizeof(t_fork) * table->number);
	if (!table->forks)
		return ;
	
}