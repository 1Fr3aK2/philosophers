#include "philosophers.h"

void set_bool(t_mutex *mutex, bool *dest, bool value)
{
    mutex_handle(mutex, LOCK);
    *dest = value;
    mutex_handle(mutex, UNLOCK);
}

bool get_bool(t_mutex *mutex, bool *value)
{
    bool src;

    mutex_handle(mutex, LOCK);
    src = *value;
    mutex_handle(mutex, UNLOCK);    
    return (src);
}

long get_long(t_mutex *mutex, long *value)
{
    long dest;
    mutex_handle(mutex, LOCK);
    dest = *value;
    mutex_handle(mutex, UNLOCK);
    return (dest);
}

void set_long(t_mutex *mutex, long *dest, long value)
{
    mutex_handle(mutex, LOCK);
    *dest = value;
    mutex_handle(mutex, UNLOCK);
}

bool simulation_finish(t_table *table)
{
    return (get_bool(&table->table_mutex, &table->end_simulation));
}