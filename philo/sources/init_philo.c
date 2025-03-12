/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:41:58 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/12 16:23:13 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	assign_philosopher_data(t_philo *philo, int id, t_data *data)
{
	philo->id = id + 1;
	philo->meals_eaten = 0;
	philo->last_meal = get_current_time();
	philo->left_fork = &data->forks[id];
	philo->right_fork = &data->forks[(id + 1) % data->n];
}

void	memory_error_handle(t_data *data, t_philo_data *arg, const char *msg)
{
	pthread_mutex_lock(&data->print_mutex);
	printf("%s\n", msg);
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_lock(&data->term_mutex);
	data->terminate = 1;
	pthread_mutex_unlock(&data->term_mutex);
	if (arg)
		free(arg);
}

void	create_philosophers(t_data *data)
{
	int				i;
	t_philo_data	*arg;

	thread_init(data);
	i = 0;
	while (i < data->n)
	{
		assign_philosopher_data(&data->p[i], i, data);
		arg = malloc(sizeof(t_philo_data));
		if (!arg)
		{
			memory_error_handle(data, NULL, "Error: malloc() fail for p data.");
			return ;
		}
		arg->philo = &data->p[i];
		arg->data = data;
		if (pthread_create(&data->p[i].thread, NULL, routine, arg) != 0)
		{
			memory_error_handle(data, arg, "Error: pthread_create() failed.");
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
