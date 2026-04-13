/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 14:30:00 by hgenc             #+#    #+#             */
/*   Updated: 2026/02/10 14:30:00 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	join_threads(t_data *data, int count)
{
	int	i;

	i = -1;
	while (++i < count)
		pthread_join(data->philos[i].thread, NULL);
}

static int	start_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, routine,
				&data->philos[i]))
		{
			pthread_mutex_lock(&data->stop_lock);
			data->stop = TRUE;
			pthread_mutex_unlock(&data->stop_lock);
			join_threads(data, i);
			return (1);
		}
	}
	return (0);
}

static int	start_sim(t_data *data)
{
	int			i;
	pthread_t	monitor_th;

	data->start_time = get_time() + 100 + data->nb_philo;
	pthread_mutex_lock(&data->meal_lock);
	i = -1;
	while (++i < data->nb_philo)
		data->philos[i].last_meal = data->start_time;
	pthread_mutex_unlock(&data->meal_lock);
	if (start_threads(data))
		return (1);
	if (pthread_create(&monitor_th, NULL, monitor, data))
	{
		pthread_mutex_lock(&data->stop_lock);
		data->stop = TRUE;
		pthread_mutex_unlock(&data->stop_lock);
		join_threads(data, data->nb_philo);
		return (1);
	}
	pthread_join(monitor_th, NULL);
	join_threads(data, data->nb_philo);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		ret;

	memset(&data, 0, sizeof(t_data));
	ret = 0;
	if (parse_args(&data, argc, argv))
		ret = 1;
	else if (init_data(&data))
		ret = 1;
	else
		ret = start_sim(&data);
	cleanup(&data);
	return (ret);
}
