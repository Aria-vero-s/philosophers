/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:41:58 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/07 18:55:56 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo_data	*philo_data;
	t_philo			*philo;
	t_data			*data;

	philo_data = (t_philo_data *)arg;
	philo = philo_data->philo;
	data = philo_data->data;
	while (1)
	{
		pick_up_forks(philo);
		eat(philo, data);
		sleep_philosopher(philo, data);
		think(philo);
		if (died(philo, data) == 0)
			break ;
	}
	return (NULL);
}

void	create_philosophers(t_data *data, t_philo_data *arr)
{
	int				i;

	i = 0;
	while (i < data->n)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			printf("Error: pthread_mutex_init() failed for fork %d.\n", i);
		i++;
	}
	i = 0;
	while (i < data->n)
	{
		data->p[i].id = i + 1;
		data->p[i].meals_eaten = 0;
		data->p[i].left_fork = &data->forks[i];
		data->p[i].right_fork = &data->forks[(i + 1) % data->n];
		arr[i].philo = &data->p[i];
		arr[i].data = data;
		if (pthread_create(&data->p[i].thread, NULL, routine, &arr[i]) != 0)
		{
			printf("Error: pthread_create() failed for %d.\n", i + 1);
			return ;
		}
		i++;
	}
}

void	init_philosophers(t_data *data)
{
	t_philo_data	*arr;

	data->p = malloc(sizeof(t_philo) * data->n);
	if (!data->p)
	{
		printf("Error: Malloc() failed for philosophers.\n");
		return ;
	}
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n);
	if (!data->forks)
	{
		printf("Error: Malloc() failed for forks.\n");
		free(data->p);
		return ;
	}
	arr = malloc(sizeof(t_philo_data) * data->n);
	if (!arr)
	{
		printf("Error: Malloc() failed for arr.\n");
		free(data->p);
		free(data->forks);
		return ;
	}
	create_philosophers(data, arr);
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

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		error_exit("error: invalid arguments");
	data.n = ft_atoi(argv[1]);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data.n_of_meals = ft_atoi(argv[5]);
	if (data.n <= 0)
	{
		printf("Error: Invalid number of philosophers\n");
		return (1);
	}
	if (pthread_mutex_init(&data.print_mutex, NULL) != 0)
	{
		printf("Error: pthread_mutex_init() failed\n");
		return (1);
	}
	init_philosophers(&data);
	join_philosophers(&data);
	free(data.p);
	return (0);
}
