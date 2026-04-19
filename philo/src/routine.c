/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 14:30:00 by hgenc             #+#    #+#             */
/*   Updated: 2026/04/19 11:09:01 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <unistd.h>

static void	sync_start(t_philo *philo)
{
	int	ready;

	ready = FALSE;
	while (!ready)
	{
		pthread_mutex_lock(&philo->data->meal_lock);
		ready = philo->data->ready;
		pthread_mutex_unlock(&philo->data->meal_lock);
		if (!ready)
			usleep(100);
	}
}

static long long	get_start_delay(t_philo *philo)
{
	if (philo->data->nb_philo % 2 == 0)
	{
		if (philo->id % 2 == 0)
			return (philo->data->time_eat / 2);
		return (0);
	}
	if (philo->id == philo->data->nb_philo)
		return ((long long)philo->data->time_eat * 2);
	if (philo->id % 2 == 0)
		return (philo->data->time_eat);
	return (0);
}

static void	think(t_philo *philo)
{
	long long	delay;

	print_status(philo, "is thinking");
	if (philo->data->nb_philo % 2 == 0)
		return ;
	delay = (long long)philo->data->time_eat * 2
		- philo->data->time_sleep;
	if (delay > 0)
		ft_usleep(delay, philo->data);
}

static void	*lone_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	ft_usleep(philo->data->time_die, philo->data);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	sync_start(philo);
	if (is_stopped(philo->data))
		return (NULL);
	if (philo->data->nb_philo == 1)
		return (lone_philo(philo));
	ft_usleep(get_start_delay(philo), philo->data);
	while (!is_stopped(philo->data))
	{
		eat(philo);
		if (is_stopped(philo->data))
			break ;
		print_status(philo, "is sleeping");
		ft_usleep(philo->data->time_sleep, philo->data);
		think(philo);
	}
	return (NULL);
}
