/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:41:58 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/14 13:54:22 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo_only(t_data *data)
{
	if (data->n == 1)
	{
		data->start_time = get_current_time();
		safe_print(data, "has taken a fork", 1, 0);
		usleep(data->time_to_die * 1000);
		safe_print(data, "died", 1, 0);
		error_exit("", data);
	}
	data->finished_count = 0;
}
