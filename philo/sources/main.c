/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:41:58 by asaulnie          #+#    #+#             */
/*   Updated: 2025/02/25 20:20:09 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philosopher_routine(void *arg)
{
    t_philo *philo;
	
	philo = (t_philo *)arg;
    printf("Philosopher %d is thinking...\n", philo->id);
    usleep(1000);
    printf("Philosopher %d is done thinking.\n", philo->id);
    return (NULL);
}

void create_philosophers(t_data *data)
{
	int	i;

	i = 0;
    data->philosophers = malloc(sizeof(t_philo) * data->n);
    if (!data->philosophers)
    {
        printf("Error: Malloc() failed.\n");
        return ;
    }
    while (i < data->n)
    {
        data->philosophers[i].id = i + 1;
        data->philosophers[i].meals_eaten = 0;
        if (pthread_create(&data->philosophers[i].thread, NULL, philosopher_routine, &data->philosophers[i]) != 0)
        {
            printf("Error: pthread_create() failed for %d.\n", i + 1);
            return ;
        }
		i++;
    }
}

void join_philosophers(t_data *data)
{
	int	i;

	i = 0;
    while (i < data->n)
	{
        pthread_join(data->philosophers[i].thread, NULL);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_data data;

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
	free(data.philosophers);
	return (0);
}
