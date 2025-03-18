/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:41:58 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/18 18:57:58 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*single_philo_routine(void *arg)
{
	t_data	*data;
	long	start_time;

	data = (t_data *)arg;
	start_time = get_current_time();
	pthread_mutex_lock(&data->forks[0]);
	safe_print(data, "has taken a fork", 1, 0);
	while (simulation_active(data))
	{
		if (get_current_time() - start_time >= data->time_to_die)
		{
			safe_print(data, "died", 1, 1);
			set_simulation_finished(data);
			break ;
		}
		usleep(1000);
	}
	pthread_mutex_unlock(&data->forks[0]);
	return (NULL);
}

int	one_philo_only(t_data *data)
{
	pthread_t	philo_thread;
	pthread_t	monitor_thread;

	if (data->n != 1)
		return (0);
	data->start_time = get_current_time();
	data->p[0].last_meal = data->start_time;
	if (pthread_create(&philo_thread, NULL, single_philo_routine, data) != 0)
		return (error_exit("Error: failed to create philo thread\n", data));
	if (pthread_create(&monitor_thread, NULL, monitor, data) != 0)
	{
		pthread_join(philo_thread, NULL);
		return (error_exit("Error: failed to create monitor thread\n", data));
	}
	pthread_join(philo_thread, NULL);
	pthread_join(monitor_thread, NULL);
	cleanup_simulation(data);
	return (1);
}
