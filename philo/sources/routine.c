/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:57:02 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/07 14:11:54 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_up_forks(t_philo *philo)
{
	printf("%d has taken a fork\n", philo->id);
}

void	eat(t_philo *philo)
{
	printf("%d is eating\n", philo->id);
	usleep(1000);
}

void	sleep_philosopher(t_philo *philo)
{
	printf("%d is sleeping\n", philo->id);
	usleep(1000);
}

void	think(t_philo *philo)
{
	printf("%d is thinking\n", philo->id);
	usleep(1000);
}

void	died(t_philo *philo)
{
	printf("%d died\n", philo->id);
}
