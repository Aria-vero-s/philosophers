/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:01:12 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/15 20:37:59 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_msg(char *msg)
{
	printf("Error: %s\n", msg);
	return (1);
}

int	is_valid_number(char *str)
{
	long	num;
	int		sign;

	num = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			return (0);
	}
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		num = num * 10 + (*str - '0');
		if ((num * sign) > INT_MAX || (num * sign) < INT_MIN)
			return (0);
		str++;
	}
	return (1);
}

int	parsing(int argc, char **argv)
{
	int		i;
	long	value;

	i = 1;
	if (argc < 5 || argc > 6)
		return (error_msg("Invalid number of arguments"));
	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
			return (error_msg("Argument invalid"));
		value = ft_atoi(argv[i]);
		if (value == 0)
			return (error_msg("Argument cannot be zero"));
		i++;
	}
	return (0);
}
