/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:41:58 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/12 19:54:41 by asaulnie         ###   ########.fr       */
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
	philo->data = data;
}

void	memory_error_handle(t_data *data, const char *msg)
{
	pthread_mutex_lock(&data->print_mutex);
	printf("%s\n", msg);
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_lock(&data->term_mutex);
	data->terminate = 1;
	pthread_mutex_unlock(&data->term_mutex);
}

void	create_philosophers(t_data *data)
{
	int				i;

	i = 0;
	thread_init(data);
	while (i < data->n)
	{
		assign_philosopher_data(&data->p[i], i, data);
		if (pthread_create(&data->p[i].thread, NULL, routine, &data->p[i]) != 0)
		{
			memory_error_handle(data, "Error: pthread_create() failed.");
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
