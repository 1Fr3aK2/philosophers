/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:47:03 by raamorim          #+#    #+#             */
/*   Updated: 2025/01/27 13:47:04 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

bool	is_digit(char c)
{
	return (c >= 48 && c <= 57);
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

bool	check_inputs(char *argv[])
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if (!check_input(argv[i]))
			return (false);
	}
	return (true);
}
