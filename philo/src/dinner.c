#include "philo.h"

static void thinking(t_philo *philo)
{
    write_status(THINKING, philo);
}


static void eat(t_philo *philo)
{
    safe_mutex_handle(&philo->first_fork->fork, LOCK);
    write_status(FIRST_FORK, philo);
    safe_mutex_handle(&philo->second_fork->fork, LOCK);
    write_status(SECOND_FORK, philo);

    set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILISECONDES));
    philo->meals_counter++;
    write_status(EATING, philo);
    my_usleep(philo->table->time_to_eat, philo->table);
    if (philo->table->nbr_limits_meals > 0 && philo->meals_counter == philo->table->nbr_limits_meals)
        set_bool(&philo->philo_mutex, &philo->full, true);
    safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
    safe_mutex_handle(&philo->second_fork->fork, UNLOCK);

}


void *dinner_simulation(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
    wait_all_threads(philo->table);

    while(!simulation_finish(philo->table))
    {
        if (philo->full)
            break;
        eat(philo);
        write_status(SLEEPING, philo);
        my_usleep(philo->table->time_to_sleep, philo->table);
        thinking(philo);
    }

    return (NULL);
}


void dinner_start(t_table *table)
{
    int i = -1;
    if (table->nbr_limits_meals == 0)
        return ;
    else if (table->nbr_limits_meals == 1)
        ; //TODO
    else
    {
        while (++i < table->philo_nbr)
            safe_thread_handle(&table->philos[i].thread_id, dinner_simulation, &table->philos[i], CREATE);
    }
    table->start_simulation = gettime(MILISECONDES);
    set_bool(&table->table_mutex, &table->all_threads_ready, true);

    i = -1;
    while(++i < table->philo_nbr)
        safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
}