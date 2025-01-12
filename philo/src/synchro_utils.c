#include "philosophers.h"

void wait_threads(t_table *table)
{
    while(!get_bool(&table->table_mutex, &table->ready))
        ;
}