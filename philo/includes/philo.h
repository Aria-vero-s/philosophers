/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:28:50 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/12 16:29:39 by asaulnie         ###   ########.fr       */
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

typedef struct s_philo	t_philo;

typedef struct s_data	t_data;

typedef struct s_philo {
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	t_data			*data;
}	t_philo;

typedef struct s_data {
	int				n;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				n_of_meals;
	long			start_time;
	int				finished_count;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	finished_mutex;
	pthread_mutex_t	term_mutex;
	t_philo			*p;
	int				terminate;
}	t_data;

typedef struct s_philo_data {
	t_philo			*philo;
	t_data			*data;
}	t_philo_data;

// ft_atoi.c
int		ft_atoi(const char *nptr);

// init_philo.c
void	thread_init(t_data *data);
void	assign_philosopher_data(t_philo *philo, int id, t_data *data);
void	memory_error_handle(t_data *data, t_philo_data *arg, const char *msg);
void	create_philosophers(t_data *data);
void	init_philosophers(t_data *data);

// init.c
void	philosopher_actions(t_philo *philo, t_data *data);
void	init_last_meals(t_data *data);
void	init_data(t_data *data);
void	setup(int argc, char **argv, t_data *data, pthread_t *monitor_thread);

// monitor.c
void	check_all_finished(t_data *data);
void	check_philosopher_death(t_data *data);
void	*monitor(void *arg);

// routine.c
void	*routine(void *arg);
void	pick_up_forks(t_philo *philo);
int		eat(t_philo *philo, t_data *data);
void	sleep_philosopher(t_philo *philo, t_data *data);
void	think(t_philo *philo);

// utils.c
long	get_current_time(void);
void	error_exit(char *msg, t_data *data);
void	join_philosophers(t_data *data);
void	cleanup_simulation(t_data *data, pthread_t monitor_thread);
void	safe_print(t_data *data, const char *msg, int philo_id, int force);

#endif