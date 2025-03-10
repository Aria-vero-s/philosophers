/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 20:19:06 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/10 20:35:39 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	error_exit(char *msg)
{
	int	len;

	len = 0;
	while (msg[len])
		len++;
	write(2, msg, len);
	exit(1);
}

void	init_data(t_data *data)
{
	if (data->n == 1)
	{
		printf("1 has taken a fork\n");
		usleep(data->time_to_die * 1000);
		printf("Philosopher 1 died\n");
		error_exit("");
	}
	data->philo_died = 0;
	data->finished_count = 0;
	data->all_eaten_printed = 0;
}
