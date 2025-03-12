/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 20:19:06 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/12 17:37:33 by asaulnie         ###   ########.fr       */
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

void	error_exit(char *msg, t_data *data)
{
	int	len;

	len = 0;
	while (msg[len])
		len++;
	write(2, msg, len);
	if (data)
	{
		if (data->p)
			free(data->p);
		if (data->forks)
			free(data->forks);
	}
	exit(1);
}

void	join_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n)
	{
		pthread_join(data->p[i].thread, NULL);
		i++;
	}
}

void	cleanup_simulation(t_data *data, pthread_t monitor_thread)
{
	join_philosophers(data);
	pthread_join(monitor_thread, NULL);
	if (data->finished_count == data->n)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("All meals eaten\n");
		pthread_mutex_unlock(&data->print_mutex);
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->finished_mutex);
	pthread_mutex_destroy(&data->term_mutex);
	free(data->p);
	free(data->forks);
}

void	safe_print(t_data *data, const char *msg, int philo_id, int force)
{
	pthread_mutex_lock(&data->term_mutex);
	if (!force && data->terminate)
	{
		pthread_mutex_unlock(&data->term_mutex);
		return ;
	}
	pthread_mutex_unlock(&data->term_mutex);
	pthread_mutex_lock(&data->print_mutex);
	if (philo_id > 0)
		printf("%d %s\n", philo_id, msg);
	else
		printf("%s\n", msg);
	pthread_mutex_unlock(&data->print_mutex);
}
