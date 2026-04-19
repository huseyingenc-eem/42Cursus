/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 14:30:00 by hgenc             #+#    #+#             */
/*   Updated: 2026/04/19 11:08:48 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <stdlib.h>

static int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (1);
	data->forks_inited = 0;
	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		data->forks_inited++;
	}
	return (0);
}

static int	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->print_lock, NULL))
		return (1);
	data->print_lock_inited = TRUE;
	if (pthread_mutex_init(&data->stop_lock, NULL))
		return (1);
	data->stop_lock_inited = TRUE;
	if (pthread_mutex_init(&data->meal_lock, NULL))
		return (1);
	data->meal_lock_inited = TRUE;
	return (0);
}

static void	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = 0;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		data->philos[i].data = data;
	}
}

int	init_data(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (error_exit("Error: allocation failed\n"));
	if (init_forks(data))
		return (error_exit("Error: mutex init failed\n"));
	if (init_mutexes(data))
		return (error_exit("Error: mutex init failed\n"));
	init_philos(data);
	return (0);
}
