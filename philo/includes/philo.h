/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:28:50 by asaulnie          #+#    #+#             */
/*   Updated: 2025/03/18 16:40:04 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <stdio.h>
# include <pthread.h>
# include <time.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo	t_philo;

struct s_philo {
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
	pthread_mutex_t meal_mutex;
};

struct s_data {
	int				n;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_of_meals;
	int				finished_count;
	int				simulation_finished;
	long			start_time;
	t_philo			*p;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	finished_mutex;
	pthread_mutex_t	term_mutex;
	int				print_mutex_init;
	int				finished_mutex_init;
	int				term_mutex_init;
	int				fork_mutexes_initialized;
	int				meal_mutexes_initialized;
};

// ft_atoi.c
int		ft_atoi(const char *nptr);

// ft_strncmp.c
int		ft_strncmp(const char *s1, const char *s2, size_t n);

// parsing.c
int		error_msg(char *msg);
int		is_valid_number(char *str);
int		parsing(int argc, char **argv);

// special_case.c
int		one_philo_only(t_data *data);

// init.c
int		arguments_to_data(int argc, char **argv, t_data *data);
int		init_mutexes(t_data *data);
void	init_philosophers(t_data *data);
int		init_simulation(int argc, char **argv, t_data *data);

// monitor.c
void	check_all_finished(t_data *data);
void	check_philosopher_death(t_data *data);
int		simulation_active(t_data *data);
void	*monitor(void *arg);

// routine.c
int		pick_up_forks(t_philo *philo);
int		eat(t_philo *philo);
int		sleep_philosopher(t_philo *philo);
int		think(t_philo *philo);
void	*routine(void *arg);

// utils.c
int		error_exit(const char *msg, t_data *data);
void	cleanup_simulation(t_data *data);
void	unlock_forks(t_philo *philo);

// simuation.c
long	get_current_time(void);
void	safe_print(t_data *data, const char *msg, int philo_id, int force);
void	set_simulation_finished(t_data *data);
int		run_simulation(t_data *data);

#endif