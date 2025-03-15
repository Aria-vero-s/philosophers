/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:01:12 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/15 14:23:44 by asaulnie         ###   ########.fr       */
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
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
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
			return (error_msg("Argument must be a positive int"));
		value = ft_atoi(argv[i]);
		if (value > INT_MAX)
			return (error_msg("Argument is bigger than INT_MAX"));
		if (value == 0)
			return (error_msg("Argument cannot be zero"));
		i++;
	}
	return (0);
}
