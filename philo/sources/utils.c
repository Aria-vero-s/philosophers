/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 20:19:06 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/18 16:41:03 by asaulnie         ###   ########.fr       */
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
	cleanup_simulation(data);
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
	if (data->print_mutex_init == 1)
		pthread_mutex_destroy(&data->print_mutex);
	if (data->finished_mutex_init == 1)
		pthread_mutex_destroy(&data->finished_mutex);
	if (data->term_mutex_init == 1)
		pthread_mutex_destroy(&data->term_mutex);
	while (i < data->fork_mutexes_initialized)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	while (i < data->meal_mutexes_initialized)
	{
		pthread_mutex_destroy(&data->p[i].meal_mutex);
		i++;
	}
	if (data->p)
		free(data->p);
	if (data->forks)
		free(data->forks);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
