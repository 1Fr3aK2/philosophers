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
