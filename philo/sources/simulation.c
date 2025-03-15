/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:49:43 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/15 15:39:50 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write(2, "gettimeofday() error\n", 22);
		return (0);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	safe_print(t_data *data, const char *msg, int philo_id, int force)
{
	int		active;
	long	timestamp;

	pthread_mutex_lock(&data->term_mutex);
	active = !data->simulation_finished;
	pthread_mutex_unlock(&data->term_mutex);
	if (!force && !active)
		return ;
	pthread_mutex_lock(&data->print_mutex);
	timestamp = get_current_time() - data->start_time;
	if (philo_id > 0)
		printf("%ld %d %s\n", timestamp, philo_id, msg);
	else
		printf("%ld %s\n", timestamp, msg);
	pthread_mutex_unlock(&data->print_mutex);
}

void	set_simulation_finished(t_data *data)
{
	pthread_mutex_lock(&data->term_mutex);
	data->simulation_finished = 1;
	pthread_mutex_unlock(&data->term_mutex);
}

void	join_all_threads(t_data *data, pthread_t monitor_thread)
{
	int	i;

	i = 0;
	while (i < data->n)
	{
		pthread_join(data->p[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
}

int	run_simulation(t_data *data)
{
	pthread_t	monitor_thread;
	int			i;

	i = 0;
	data->start_time = get_current_time();
	while (i < data->n)
	{
		data->p[i].last_meal = data->start_time;
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor, data) == 1)
		return (error_exit("Error: failed to create monitor thread\n", data));
	i = 0;
	while (i < data->n)
	{
		if (pthread_create(&data->p[i].thread, NULL, routine, &data->p[i]) == 1)
		{
			safe_print(data, "Error: failed to create philo thread", 0, 1);
			set_simulation_finished(data);
			return (-1);
		}
		i++;
	}
	join_all_threads(data, monitor_thread);
	return (0);
}
