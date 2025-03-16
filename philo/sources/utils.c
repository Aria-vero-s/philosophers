/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 20:19:06 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/16 17:36:54 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_exit(const char *msg, t_data *data)
{
	int	len;

	len = 0;
	while (msg[len])
		len++;
	if (msg && len > 0)
		write(2, msg, len);
	if (data)
	{
		if (data->p)
			free(data->p);
		if (data->forks)
			free(data->forks);
	}
	return (-1);
}

void	cleanup_simulation(t_data *data)
{
	int	i;

	i = 0;
	if (data->finished_count == data->n)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("All meals eaten\n");
		pthread_mutex_unlock(&data->print_mutex);
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->finished_mutex);
	pthread_mutex_destroy(&data->term_mutex);
	while (i < data->n)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->p);
	free(data->forks);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
