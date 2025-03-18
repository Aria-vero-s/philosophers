/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:01:12 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/18 18:20:35 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_msg(char *msg)
{
	printf("Error: %s\n", msg);
	return (1);
}

int	parsing(const char *str, int *result)
{
	int		i;
	long	value;

	i = 0;
	if (!str || !*str)
		return (error_msg("Argument invalid"));
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (error_msg("Argument must be positive int"));
		i++;
	}
	value = ft_atoi(str);
	if (value <= 0)
		return (error_msg("Argument must be positive and non-zero"));
	*result = (int)value;
	return (0);
}
