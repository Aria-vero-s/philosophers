/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:41:58 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/06 19:57:23 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	while (1)
	{
		think(philo);
		pick_up_forks(philo);
		eat(philo);
		put_down_forks(philo);
		sleep_philosopher(philo);
	}
}

void	create_philosophers(t_data *data)
{
	int	i;

	i = 0;
	data->p = malloc(sizeof(t_philo) * data->n);
	if (!data->p)
	{
		printf("Error: Malloc() failed.\n");
		return ;
	}
	while (i < data->n)
	{
		data->p[i].id = i + 1;
		data->p[i].meals_eaten = 0;
		if (pthread_create(&data->p[i].thread, NULL, routine, &data->p[i]) != 0)
		{
			printf("Error: pthread_create() failed for %d.\n", i + 1);
			return ;
		}
		i++;
	}
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
		printf("Error: Invalid number of philosophers.\n");
		return (1);
	}
	create_philosophers(&data);
	join_philosophers(&data);
	free(data.p);
	return (0);
}
