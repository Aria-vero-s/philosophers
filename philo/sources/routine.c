/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:57:02 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/07 18:56:49 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_up_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	printf("%d has taken a fork\n", philo->id);
}

void	eat(t_philo *philo, t_data *data)
{
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
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
	if (get_current_time() - philo->last_meal_time > data->time_to_die)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("Philosopher %d died\n", philo->id);
		pthread_mutex_unlock(&data->print_mutex);
		data->philo_died = 1;
		return (0);
	}
	return (1);
}
