/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:44:45 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/11 14:48:12 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_last_meals(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n)
	{
		data->p[i].last_meal = data->start_time;
		i++;
	}
}

void	setup(int argc, char **argv, t_data *data, pthread_t *monitor_thread)
{
	if (argc < 5 || argc > 6)
		error_exit("error: invalid arguments\n");
	data->n = ft_atoi(argv[1]);
	if (data->n <= 0)
		error_exit("error: invalid n of philosophers\n");
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->n_of_meals = ft_atoi(argv[5]);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		error_exit("error: pthread_mutex_init() failed\n");
	if (pthread_mutex_init(&data->finished_mutex, NULL) != 0)
		error_exit("error: pthread_mutex_init() failed for finished_mutex\n");
	init_data(data);
	init_philosophers(data);
	data->start_time = get_current_time();
	init_last_meals(data);
	if (pthread_create(monitor_thread, NULL, monitor, data) != 0)
		error_exit("Error: pthread_create() failed for monitor\n");
}

void	cleanup_simulation(t_data *data, pthread_t monitor_thread)
{
	join_philosophers(data);
	pthread_join(monitor_thread, NULL);
	if (data->finished_count == data->n)
		printf("All meals eaten\n");
	free(data->p);
	free(data->forks);
}
