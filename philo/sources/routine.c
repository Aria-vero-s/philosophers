/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:57:02 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/12 19:55:09 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo			*philo;
	t_data			*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&data->term_mutex);
		if (data->terminate)
		{
			pthread_mutex_unlock(&data->term_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->term_mutex);
		pick_up_forks(philo);
		if (!eat(philo, data))
			break ;
		sleep_philosopher(philo, data);
		think(philo);
	}
	return (NULL);
}

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
	safe_print(philo->data, "has taken a fork", philo->id, 0);
}

int	eat(t_philo *philo, t_data *data)
{
	philo->last_meal = get_current_time();
	safe_print(philo->data, "is eating", philo->id, 0);
	philo->meals_eaten++;
	if (data->n_of_meals != -1 && philo->meals_eaten >= data->n_of_meals)
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
	safe_print(philo->data, "is sleeping", philo->id, 0);
	usleep(data->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	safe_print(philo->data, "is thinking", philo->id, 0);
	usleep(1000);
}
