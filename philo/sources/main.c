/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:41:58 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/10 21:34:39 by asaulnie         ###   ########.fr       */
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
		if (data->philo_died == 1)
			error_exit("");
		pick_up_forks(philo);
		if (eat(philo, data) == 0)
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			break ;
		}
		sleep_philosopher(philo, data);
		think(philo);
		died(philo, data);
	}
	return (NULL);
}

void	create_philosophers(t_data *data, t_philo_data *arr)
{
	int	i;

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

// void	*monitor(void *arg)
// {
// 	t_data	*data = (t_data *)arg;
// 	int		i;

// 	while (!data->philo_died)
// 	{
// 		i = 0;
// 		while (i < data->n)
// 		{
// 			if (get_current_time() - data->p[i].last_meal_time > data->time_to_die)
// 			{
// 				pthread_mutex_lock(&data->print_mutex);
// 				printf("Philosopher %d died\n", data->p[i].id);
// 				data->philo_died = 1;
// 				pthread_mutex_unlock(&data->print_mutex);
// 				return (NULL);
// 			}
// 			i++;
// 		}
// 		usleep(1000);
// 	}
// 	return (NULL);
// }


int	main(int argc, char **argv)
{
	t_data	data;
	// pthread_t	monitor_thread;

	if (argc < 5 || argc > 6)
		error_exit("error: invalid arguments\n");
	data.n = ft_atoi(argv[1]);
	if (data.n <= 0)
		error_exit("error: invalid n of philosophers\n");
	if (pthread_mutex_init(&data.print_mutex, NULL) != 0)
		error_exit("error: pthread_mutex_init() failed\n");
	init_data(&data);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data.n_of_meals = ft_atoi(argv[5]);
	if (pthread_mutex_init(&data.finished_mutex, NULL) != 0)
		error_exit("error: pthread_mutex_init() failed for finished_mutex\n");
	// if (pthread_create(&monitor_thread, NULL, monitor, &data) != 0)
	// 	error_exit("Error: pthread_create() failed for monitor\n");
	init_philosophers(&data);
	join_philosophers(&data);
	// pthread_join(monitor_thread, NULL);
	if (data.finished_count == data.n)
		printf("All meals eaten\n");
	free(data.p);
	return (0);
}
