/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:45:44 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/16 17:29:35 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (parsing(argc, argv) != 0)
		return (-1);
	if (init_simulation(argc, argv, &data) != 0)
		return (-1);
	if (one_philo_only(&data))
		return (0);
	if (run_simulation(&data) != 0)
		return (-1);
	cleanup_simulation(&data);
	return (0);
}
