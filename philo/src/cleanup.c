/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 14:30:00 by hgenc             #+#    #+#             */
/*   Updated: 2026/02/10 14:30:00 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	cleanup(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = -1;
		while (++i < data->forks_inited)
			pthread_mutex_destroy(&data->forks[i]);
		free(data->forks);
	}
	if (data->print_lock_inited)
		pthread_mutex_destroy(&data->print_lock);
	if (data->stop_lock_inited)
		pthread_mutex_destroy(&data->stop_lock);
	if (data->meal_lock_inited)
		pthread_mutex_destroy(&data->meal_lock);
	if (data->philos)
		free(data->philos);
}
