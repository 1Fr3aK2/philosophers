/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:46:54 by raamorim          #+#    #+#             */
/*   Updated: 2025/01/27 13:46:55 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char *argv[])
{
	t_table	table;

	if ((argc < 5 || argc > 6) || !check_inputs(argv))
		return (error_exit("Error: Invalid input"), -1);
	else
	{
		if (!parse(&table, argv))
			return (error_exit("Error: parsing"), -1);
		if (!data_init(&table))
			return (error_exit("Error initializing data"), -1);
		if (!dinner_start(&table))
			return (error_exit("Error starting dinner"), clean(&table), -1);
		clean(&table);
	}
}
