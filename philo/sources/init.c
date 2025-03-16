/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:44:45 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/16 22:15:19 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data)
{
	data->p = NULL;
	data->forks = NULL;
	data->finished_count = 0;
	data->simulation_finished = 0;
	data->print_mutex_init = 0;
	data->finished_mutex_init = 0;
	data->term_mutex_init = 0;
	data->fork_mutexes_initialized = 0;
}

int	arguments_to_data(int argc, char **argv, t_data *data)
{
	data->n = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->n_of_meals = ft_atoi(argv[5]);
	else
		data->n_of_meals = -1;
	data->finished_count = 0;
	data->simulation_finished = 0;
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

int	init_mutexes(t_data *data)
{
	data->print_mutex_init = 0;
	data->finished_mutex_init = 0;
	data->term_mutex_init = 0;
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

int	init_simulation(int argc, char **argv, t_data *data)
{
	int	i;

	i = 0;
	init_data(data);
	if (arguments_to_data(argc, argv, data) != 0)
		return (-1);
	data->p = malloc(sizeof(t_philo) * data->n);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n);
	if (!data->p || !data->forks)
		return (error_exit("Error: philo malloc failed\n", data));
	init_philosophers(data);
	if (init_mutexes(data) == -1)
		return (-1);
	while (i < data->n)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (error_exit("Error: fork init failed\n", data));
		data->fork_mutexes_initialized++;
		i++;
	}
	return (0);
}
