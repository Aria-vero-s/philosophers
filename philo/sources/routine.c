/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:57:02 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/06 19:59:38 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo)
{
	printf("Philosopher %d is thinking...\n", philo->id);
	usleep(1000);
}

void	pick_up_forks(t_philo *philo)
{
	printf("Philosopher %d is picking up forks...\n", philo->id);
}

void	eat(t_philo *philo)
{
	printf("Philosopher %d is eating...\n", philo->id);
	usleep(1000);
}

void	put_down_forks(t_philo *philo)
{
	printf("Philosopher %d is putting down forks...\n", philo->id);
}

void	sleep_philosopher(t_philo *philo)
{
	printf("Philosopher %d is sleeping...\n", philo->id);
	usleep(1000);
}
