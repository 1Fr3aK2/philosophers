#include "philosophers.h"

char	*check_input(const char *str)
{
	const char	*nb;

	if (!str)
		return (NULL);
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	if (*str == '-')
		return (NULL);
	if (!is_digit(*str))
		return (NULL);
	nb = str;
	while (*nb)
	{
		if (!is_digit(*nb))
			return (NULL);
		nb++;
	}
	return ((char *)str);
}

static long	ft_atol(const char *str)
{
	long	nb;

	if (!str)
		return (-1);
	str = check_input(str);
	nb = 0;
	while (*str >= 48 && *str <= 57)
	{
		nb *= 10;
		nb += *str - 48;
		str++;
	}
	return (nb);
}

bool	parse(t_table *table, char *argv[])
{
	table->number = ft_atol(argv[1]);
	if (table->number > INT_MAX || table->number < 1)
		return (false);
	table->time_to_die = ft_atol(argv[2]);
	if (table->time_to_die > INT_MAX || table->time_to_die < 1)
		return (false);
	table->time_to_eat = ft_atol(argv[3]);
	if (table->time_to_eat > INT_MAX || table->time_to_eat < 1)
		return (false);
	table->time_to_sleep = ft_atol(argv[4]);
	if (table->time_to_sleep > INT_MAX || table->time_to_sleep < 1)
		return (false);
	return (true);
}
