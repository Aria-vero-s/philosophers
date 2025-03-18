/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:34:19 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/18 17:46:08 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_all_finished(t_data *data)
{
	pthread_mutex_lock(&data->finished_mutex);
	if (data->finished_count == data->n)
	{
		pthread_mutex_unlock(&data->finished_mutex);
		set_simulation_finished(data);
		return ;
	}
	pthread_mutex_unlock(&data->finished_mutex);
}

void	check_philosopher_death(t_data *data)
{
	int		i;
	long	last_meal;

	i = 0;
	while (i < data->n)
	{
		pthread_mutex_lock(&data->p[i].meal_mutex);
		last_meal = data->p[i].last_meal;
		pthread_mutex_unlock(&data->p[i].meal_mutex);
		if (get_current_time() - last_meal > data->time_to_die)
		{
			if (simulation_active(data))
			{
				set_simulation_finished(data);
				safe_print(data, "died", data->p[i].id, 1);
			}
			return ;
		}
		i++;
	}
}

int	simulation_active(t_data *data)
{
	int	active;

	pthread_mutex_lock(&data->term_mutex);
	if (data->simulation_finished == 0)
		active = 1;
	else
		active = 0;
	pthread_mutex_unlock(&data->term_mutex);
	return (active);
}

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	if (data->n_of_meals)
	{
		while (simulation_active(data))
		{
			check_all_finished(data);
			if (simulation_active(data))
				check_philosopher_death(data);
		}
	}
	else
	{
		while (simulation_active(data))
		{
			if (simulation_active(data))
				check_philosopher_death(data);
		}
	}
	return (NULL);
}
