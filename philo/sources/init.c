/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:44:45 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/17 21:08:30 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arguments_to_data(int argc, char **argv, t_data *data)
{
	data->n = atoi(argv[1]);
	if (data->n <= 0)
		return (error_exit("Error\n", data));
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		data->n_of_meals = atoi(argv[5]);
	else
		data->n_of_meals = -1;
	data->finished_count = 0;
	data->simulation_finished = 0;
	return (0);
}

int	init_mutexes(t_data *data)
{
	data->print_mutex_init = 0;
	data->finished_mutex_init = 0;
	data->term_mutex_init = 0;
	data->fork_mutexes_initialized = 0;
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (error_exit("Error: init failed for print_mutex\n", data));
	data->print_mutex_init = 1;
	if (pthread_mutex_init(&data->finished_mutex, NULL) != 0)
		return (error_exit("Error: init failed for finished_mutex\n", data));
	data->finished_mutex_init = 1;
	if (pthread_mutex_init(&data->term_mutex, NULL) != 0)
		return (error_exit("Error: init failed for term_mutex\n", data));
	data->term_mutex_init = 1;
	return (0);
}

void	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n)
	{
		data->p[i].id = i + 1;
		data->p[i].meals_eaten = 0;
		data->p[i].last_meal = 0;
		data->p[i].left_fork = &data->forks[i];
		data->p[i].right_fork = &data->forks[(i + 1) % data->n];
		data->p[i].data = data;
		i++;
	}
}

int	init_simulation(int argc, char **argv, t_data *data)
{
	int	i;

	i = 0;
	arguments_to_data(argc, argv, data);
	init_mutexes(data);
	data->p = NULL;
	data->forks = NULL;
	data->p = malloc(sizeof(t_philo) * data->n);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n);
	if (!data->p || !data->forks)
		return (error_exit("Error: philo malloc failed\n", data));
	while (i < data->n)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			safe_print(data, "Error: fork init failed", 0, 1);
			data->fork_mutexes_initialized = i;
			return (error_exit("Error: fork init failed\n", data));
		}
		data->fork_mutexes_initialized++;
		i++;
	}
	init_philosophers(data);
	return (0);
}
