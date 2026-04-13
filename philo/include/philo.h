/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 14:30:00 by hgenc             #+#    #+#             */
/*   Updated: 2026/02/10 14:30:00 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define TRUE 1
# define FALSE 0

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	int					meals_eaten;
	long long			last_meal;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_data				*data;
}						t_philo;

struct					s_data
{
	int					nb_philo;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					nb_meals;
	int					stop;
	long long			start_time;
	int					forks_inited;
	int					print_lock_inited;
	int					stop_lock_inited;
	int					meal_lock_inited;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		stop_lock;
	pthread_mutex_t		meal_lock;
	t_philo				*philos;
};

/* parse.c */
int						parse_args(t_data *data, int ac, char **av);

/* init.c */
int						init_data(t_data *data);

/* actions.c */
void					eat(t_philo *philo);

/* routine.c */
void					*routine(void *arg);

/* monitor.c */
void					*monitor(void *arg);

/* utils.c */
long long				get_time(void);
void					ft_usleep(long long ms);
void					print_status(t_philo *philo, char *msg);
int						is_stopped(t_data *data);
int						error_exit(char *msg);

/* cleanup.c */
void					cleanup(t_data *data);

#endif
