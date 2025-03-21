/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:57:02 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/18 18:03:03 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pick_up_forks(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	if (!data->simulation_finished)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		safe_print(philo->data, "has taken a fork", philo->id, 0);
		pthread_mutex_unlock(&philo->data->print_mutex);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	return (1);
}

int	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	if (data->simulation_finished)
	{
		unlock_forks(philo);
		return (0);
	}
	eat_helper(philo);
	philo->meals_eaten++;
	if (data->n_of_meals != -1 && philo->meals_eaten >= data->n_of_meals)
	{
		pthread_mutex_lock(&data->finished_mutex);
		data->finished_count++;
		pthread_mutex_unlock(&data->finished_mutex);
		unlock_forks(philo);
		return (0);
	}
	usleep(data->time_to_eat * 1000);
	unlock_forks(philo);
	return (1);
}

int	sleep_philosopher(t_philo *philo)
{
	if (philo->data->simulation_finished)
		return (1);
	pthread_mutex_lock(&philo->data->print_mutex);
	safe_print(philo->data, "is sleeping", philo->id, 0);
	pthread_mutex_unlock(&philo->data->print_mutex);
	usleep(philo->data->time_to_sleep * 1000);
	return (0);
}

int	think(t_philo *philo)
{
	if (philo->data->simulation_finished)
		return (1);
	pthread_mutex_lock(&philo->data->print_mutex);
	safe_print(philo->data, "is thinking", philo->id, 0);
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (simulation_active(data))
	{
		if (pick_up_forks(philo))
			break ;
		if (!eat(philo))
			break ;
		if (sleep_philosopher(philo))
			break ;
		think(philo);
	}
	return (NULL);
}
