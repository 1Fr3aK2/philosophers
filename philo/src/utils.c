#include "philosophers.h"

void	exit_msg(char *str)
{
	if (!str)
		printf("Leaving, no msg passed\n");
	else
		printf("%s\n", str);
}

bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

bool	is_digit(char c)
{
	return (c >= 48 && c <= 57);
}

bool	check_inputs(char *argv[])
{
	int i;

	i = 0;
	while (argv[++i])
	{
		if (!check_input(argv[i]))
			return (false);
	}
	return (true);
}

long gettime(t_time time)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (exit_msg("Error with gettimeofday"), -1);
	if (time == SECONDS)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (time == MILISECONDES)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (time == MIRCOSECONDS)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		return (exit_msg("Wrong input"), -1);
	return (1);
}

void my_usleep(long usec, t_table *table)
{
	long start;
	long passed;
	long left;

	start = gettime(MIRCOSECONDS);
	while(gettime(MIRCOSECONDS) - start < usec)
	{
		//se ja tiver acabado break;
		if (simulation_finish(table))
			break;
		passed = gettime(MIRCOSECONDS) - start;
		left = usec - passed;
		if (left > 1e3)
			usleep(usec/2);
		else
		{
			while(gettime(MIRCOSECONDS) - start < usec)
				;
		}
	}
}