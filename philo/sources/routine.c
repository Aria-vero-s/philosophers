/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:57:02 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/11 14:33:25 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_up_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	printf("%d has taken a fork\n", philo->id);
}

int	eat(t_philo *philo, t_data *data)
{
	philo->last_meal = get_current_time();
	printf("%d is eating\n", philo->id);
	philo->meals_eaten++;
	if (philo->meals_eaten == data->n_of_meals)
	{
		pthread_mutex_lock(&data->finished_mutex);
		data->finished_count++;
		pthread_mutex_unlock(&data->finished_mutex);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}	
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (1);
}

void	sleep_philosopher(t_philo *philo, t_data *data)
{
	usleep(data->time_to_sleep * 1000);
	printf("%d is sleeping\n", philo->id);
	usleep(1000);
}

void	think(t_philo *philo)
{
	printf("%d is thinking\n", philo->id);
	usleep(1000);
}

int	died(t_philo *philo, t_data *data)
{
	if (get_current_time() - philo->last_meal > data->time_to_die)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("Philosopher %d died\n", philo->id);
		pthread_mutex_unlock(&data->print_mutex);
		data->philo_died = 1;
		return (0);
	}
	return (1);
}
