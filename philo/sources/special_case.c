/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:41:58 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/12 20:04:50 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo_only(t_data *data)
{
	if (data->n == 1)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("1 has taken a fork\n");
		pthread_mutex_unlock(&data->print_mutex);
		usleep(data->time_to_die * 1000);
		pthread_mutex_lock(&data->print_mutex);
		printf("1 died\n");
		pthread_mutex_unlock(&data->print_mutex);
		error_exit("", data);
	}
	data->finished_count = 0;
}
