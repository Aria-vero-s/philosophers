/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:45:44 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/12 16:12:52 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor_thread;

	data.p = NULL;
	data.forks = NULL;
	setup(argc, argv, &data, &monitor_thread);
	cleanup_simulation(&data, monitor_thread);
	return (0);
}
