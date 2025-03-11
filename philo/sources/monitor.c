/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:34:19 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/11 14:37:44 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_all_finished(t_data *data)
{
	pthread_mutex_lock(&data->finished_mutex);
	if (data->finished_count == data->n)
	{
		pthread_mutex_unlock(&data->finished_mutex);
		pthread_exit(NULL);
	}
	pthread_mutex_unlock(&data->finished_mutex);
}

void	check_philosopher_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n)
	{
		if (get_current_time() - data->p[i].last_meal > data->time_to_die)
		{
			pthread_mutex_lock(&data->print_mutex);
			if (!data->philo_died)
			{
				printf("Philosopher %d died\n", data->p[i].id);
				data->philo_died = 1;
			}
			pthread_mutex_unlock(&data->print_mutex);
			exit(1);
		}
		i++;
	}
}

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		check_all_finished(data);
		check_philosopher_death(data);
		usleep(1000);
	}
	return (NULL);
}
