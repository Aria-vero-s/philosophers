/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:44:45 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/12 20:06:55 by asaulnie         ###   ########.fr       */
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

void	thread_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			pthread_mutex_lock(&data->print_mutex);
			printf("Error: pthread_mutex_init() failed for fork %d.\n", i);
			pthread_mutex_unlock(&data->print_mutex);
		}
		i++;
	}
}

void	create_philosophers(t_data *data)
{
	int				i;

	i = 0;
	thread_init(data);
	while (i < data->n)
	{
		data->p[i].id = i + 1;
		data->p[i].meals_eaten = 0;
		data->p[i].last_meal = get_current_time();
		data->p[i].left_fork = &data->forks[i];
		data->p[i].right_fork = &data->forks[(i + 1) % data->n];
		data->p[i].data = data;
		if (pthread_create(&data->p[i].thread, NULL, routine, &data->p[i]) != 0)
		{
			pthread_mutex_lock(&data->print_mutex);
			printf("Error: pthread_create() failed\n");
			pthread_mutex_unlock(&data->print_mutex);
			pthread_mutex_lock(&data->term_mutex);
			data->terminate = 1;
			pthread_mutex_unlock(&data->term_mutex);
			return ;
		}
		i++;
	}
}

void	init_philosophers(t_data *data)
{
	data->p = malloc(sizeof(t_philo) * data->n);
	if (!data->p)
		error_exit("Error: malloc() failed for philosophers.\n", data);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n);
	if (!data->forks)
	{
		free(data->p);
		error_exit("Error: malloc() failed for forks.\n", data);
	}
	create_philosophers(data);
}

void	setup(int argc, char **argv, t_data *data, pthread_t *monitor_thread)
{
	if (argc < 5 || argc > 6)
		error_exit("error: invalid arguments\n", data);
	data->n = ft_atoi(argv[1]);
	if (data->n <= 0)
		error_exit("error: invalid n of philosophers\n", data);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->n_of_meals = ft_atoi(argv[5]);
	else
		data->n_of_meals = -1;
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		error_exit("error: pthread_mutex_init() failed\n", data);
	if (pthread_mutex_init(&data->finished_mutex, NULL) != 0)
		error_exit("error: pthread_mutex_init() failed\n", data);
	if (pthread_mutex_init(&data->term_mutex, NULL) != 0)
		error_exit("error: pthread_mutex_init() failed for term_mutex\n", data);
	data->terminate = 0;
	one_philo_only(data);
	init_philosophers(data);
	data->start_time = get_current_time();
	init_last_meals(data);
	if (pthread_create(monitor_thread, NULL, monitor, data) != 0)
		error_exit("Error: pthread_create() failed for monitor\n", data);
}
