#include "../includes/philo.h"

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

bool	parse(t_table *table, char **argv)
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
	if (table->time_to_die < 6e4 || table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		error_exit("use timestamps bigger than 60ms");
	if (argv[5])
	{
		table->nbr_limits_meals = ft_atol(argv[5]);
		if (table->nbr_limits_meals > INT_MAX || table->nbr_limits_meals < 1)
			return (false);
	}
	else
		table->nbr_limits_meals = -1;
	return (true);
}
