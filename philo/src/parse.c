#include "philo.h"

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


bool parse(t_table *table, char **argv)
{
    table->philo_nbr = ft_atol(argv[1]);
    if (table->philo_nbr > INT_MAX || table->philo_nbr < 1)
        return (false);

    table->time_to_die = ft_atol(argv[2]) * 1e3;
    if (table->time_to_die > INT_MAX || table->time_to_die < 1)
        return (false);

    table->time_to_eat = ft_atol(argv[3]) * 1e3;
    if (table->time_to_eat > INT_MAX || table->time_to_eat < 1)
        return (false);

    table->time_to_sleep = ft_atol(argv[4]) * 1e3;
    if (table->time_to_sleep > INT_MAX || table->time_to_sleep < 1)
        return (false);

    if (table->time_to_die < 6e4 || table->time_to_eat < 6e4 || table->time_to_sleep < 6e4)
        error_exit("use timestamps bigger than 60ms");

    if (argv[5])
        table->nbr_limits_meals = ft_atol(argv[5]);
    else
        table->nbr_limits_meals = -1;

    return (true);
}


