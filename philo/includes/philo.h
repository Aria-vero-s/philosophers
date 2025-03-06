/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:28:50 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/06 20:01:06 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <time.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philo {
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
}	t_philo;

typedef struct s_data {
	int				n;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				n_of_meals;
	long			start_time;
	int				simulation_end;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	t_philo			*p;
}	t_data;

int		ft_atoi(const char *nptr);
void	error_exit(char *msg);
void	*routine(void *arg);
void	create_philosophers(t_data *data);
void	join_philosophers(t_data *data);
void	think(t_philo *philo);
void	pick_up_forks(t_philo *philo);
void	eat(t_philo *philo);
void	put_down_forks(t_philo *philo);
void	sleep_philosopher(t_philo *philo);

#endif