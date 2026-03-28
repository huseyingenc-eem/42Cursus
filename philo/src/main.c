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

static int	start_sim(t_data *data)
{
	int			i;
	pthread_t	monitor_th;

	data->start_time = get_time();
	i = -1;
	while (++i < data->nb_philo)
		data->philos[i].last_meal = data->start_time;
	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, routine,
				&data->philos[i]))
			return (1);
	}
	if (pthread_create(&monitor_th, NULL, monitor, data))
		return (1);
	pthread_join(monitor_th, NULL);
	i = -1;
	while (++i < data->nb_philo)
		pthread_join(data->philos[i].thread, NULL);
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
		start_sim(&data);
	cleanup(&data);
	return (ret);
}
