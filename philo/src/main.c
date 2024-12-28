#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_table table;

	if (argc != 5 || !check_inputs(argv))
		return (printf("Error: Invalid input\n"));
	else
	{
		if (!parse(&table, argv))
			return (printf("Error: parsing"));
        struct_init(&table);
    }
}
