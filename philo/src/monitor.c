/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 14:30:00 by hgenc             #+#    #+#             */
/*   Updated: 2026/02/10 14:30:00 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	set_stop(t_data *data)
{
	pthread_mutex_lock(&data->stop_lock);
	data->stop = TRUE;
	pthread_mutex_unlock(&data->stop_lock);
}

static int	check_death(t_data *data)
{
	int			i;
	long long	time;

	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_mutex_lock(&data->meal_lock);
		time = get_time() - data->philos[i].last_meal;
		pthread_mutex_unlock(&data->meal_lock);
		if (time > data->time_die)
		{
			set_stop(data);
			pthread_mutex_lock(&data->print_lock);
			printf("%lld %d died\n", get_time() - data->start_time,
				data->philos[i].id);
			pthread_mutex_unlock(&data->print_lock);
			return (TRUE);
		}
	}
	return (FALSE);
}

static int	check_all_ate(t_data *data)
{
	int	i;
	int	done;

	if (data->nb_meals == -1)
		return (FALSE);
	done = 0;
	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_mutex_lock(&data->meal_lock);
		if (data->philos[i].meals_eaten >= data->nb_meals)
			done++;
		pthread_mutex_unlock(&data->meal_lock);
	}
	if (done == data->nb_philo)
	{
		set_stop(data);
		return (TRUE);
	}
	return (FALSE);
}

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_death(data) || check_all_ate(data))
			break ;
		usleep(500);
	}
	return (NULL);
}
