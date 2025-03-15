/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:45:44 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/15 21:02:24 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (parsing(argc, argv) == 1)
		return (-1);
	if (init_simulation(argc, argv, &data) == 1)
		return (-1);
	if (one_philo_only(&data) == 1)
		return (-1);
	if (run_simulation(&data) == 1)
		return (-1);
	cleanup_simulation(&data);
	return (0);
}
