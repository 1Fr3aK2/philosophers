#include "philo.h"

void error_exit (const char *error)
{
    printf("%s\n", error);
}

void my_usleep(long usec, t_table *table)
{
    long start;
    long elapsed;
    long rem;

    start = gettime(MIRCOSECONDS);
    while(gettime(MIRCOSECONDS) - start < usec)
    {
        if (simulation_finish(table))
            break;
        elapsed = gettime(MIRCOSECONDS) - start;
        rem = usec - elapsed;
        if (rem > 1e3)
            usleep(usec / 2);
        else
        {
            while(gettime(MIRCOSECONDS) - start < usec)
                ;
        }
    }
}



long gettime(t_time time)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL))
        error_exit("Gettimeofday failed");
    if (time == SECONDS)
        return (tv.tv_sec + (tv.tv_usec / 1e6));
    else if (time == MILISECONDES)
        return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
    else if (time == MIRCOSECONDS)
        return ((tv.tv_sec * 1e6) + tv.tv_usec);
    else
        error_exit("Wrong input\n");
    return (1337);

}