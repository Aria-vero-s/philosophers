/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:41:58 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/15 15:40:52 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_philo_only(t_data *data)
{
	if (data->n == 1)
	{
		data->start_time = get_current_time();
		pthread_mutex_lock(&data->forks[0]);
		safe_print(data, "has taken a fork", 1, 0);
		usleep(data->time_to_die * 1000);
		safe_print(data, "died", 1, 0);
		pthread_mutex_unlock(&data->forks[0]);
		return (error_exit("", data));
	}
	return (0);
}
