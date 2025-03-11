/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:28:50 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/11 14:47:48 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <time.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo {
	int				id;
	int				meals_eaten;
	long			last_meal;
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
	int				philo_died;
	int				finished_count;
	pthread_mutex_t	finished_mutex;
	int				all_eaten_printed;
}	t_data;

typedef struct s_philo_data {
	t_philo			*philo;
	t_data			*data;
}	t_philo_data;

int		ft_atoi(const char *nptr);
void	error_exit(char *msg);
void	*routine(void *arg);
void	init_philosophers(t_data *data);
void	thread_init(t_data *data);
void	create_philosophers(t_data *data, t_philo_data *arr);
void	join_philosophers(t_data *data);
void	pick_up_forks(t_philo *philo);
int		eat(t_philo *philo, t_data *data);
void	sleep_philosopher(t_philo *philo, t_data *data);
void	think(t_philo *philo);
int		died(t_philo *philo, t_data *data);
long	get_current_time(void);
void	init_data(t_data *data);
void	*monitor(void *arg);
void	check_philosopher_death(t_data *data);
void	check_all_finished(t_data *data);
void	cleanup_simulation(t_data *data, pthread_t monitor_thread);
void	setup(int argc, char **argv, t_data *data, pthread_t *monitor_thread);
void	init_last_meals(t_data *data);

#endif