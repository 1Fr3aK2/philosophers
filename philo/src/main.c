#include "../includes/philo.h"

int	main(int argc, char *argv[])
{
	t_table	table;

	if ((argc < 5 && argc > 6) || !check_inputs(argv))
		return (printf("Error: Invalid input\n"));
	else
	{
		if (!parse(&table, argv))
			return (printf("Error: parsing"));
		if (!data_init(&table))
			return (error_exit("Error initializing data"), -1);
		if (!dinner_start(&table))
			return (error_exit("Error starting dinner"), clean(&table), -1);
		clean(&table);
	}
}
