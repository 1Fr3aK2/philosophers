#include "philo.h"

static void assign_forks(t_philo *philo, t_fork *forks, int position)
{
    int philo_nbr;
    philo_nbr = philo->table->philo_nbr;
    
    philo->first_fork = &forks[(position + 1) % philo_nbr];
    philo->second_fork = &forks[position];

    if (philo->id % 2 == 0)
    {
        philo->first_fork = &forks[position];
        philo->second_fork = &forks[(position + 1) % philo_nbr];
    }
}

static void philo_init(t_table *table)
{
    int i;
    t_philo *philo;

    i = -1;
    while(++i < table->philo_nbr)
    {
        philo = table->philos + i;
        philo->id = i + 1;
        philo->full = false;
        philo->meals_counter = 0;
        philo->table = table;
        safe_mutex_handle(&philo->philo_mutex, INIT);
        assign_forks(philo, table->forks, i);
    }
}

void data_init(t_table *table)
{
    int i;

    i = -1;
    table->end_simulation = false;
    table->all_threads_ready = false;
    table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
    if (!table->philos)
        return (error_exit("Error w/malloc\n"));
    safe_mutex_handle(&table->table_mutex, INIT);
    safe_mutex_handle(&table->write_mutex, INIT);
    table->forks = malloc(sizeof(t_fork) * table->philo_nbr);
    if (!table->forks)
        return (error_exit("Error w/malloc\n"));
    while(++i < table->philo_nbr)
    {
        safe_mutex_handle(&table->forks[i].fork, INIT);
        table->forks[i].fork_id = i;
    }
    philo_init(table);
}