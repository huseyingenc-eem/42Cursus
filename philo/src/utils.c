/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 14:30:00 by hgenc             #+#    #+#             */
/*   Updated: 2026/02/10 14:30:00 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long long ms)
{
	long long	start;

	start = get_time();
	while (get_time() - start < ms)
		usleep(200);
}

void	print_status(t_philo *philo, char *msg)
{
	long long	time;

	pthread_mutex_lock(&philo->data->print_lock);
	if (!is_stopped(philo->data))
	{
		time = get_time() - philo->data->start_time;
		printf("%lld %d %s\n", time, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->print_lock);
}

int	is_stopped(t_data *data)
{
	int	stopped;

	pthread_mutex_lock(&data->stop_lock);
	stopped = data->stop;
	pthread_mutex_unlock(&data->stop_lock);
	return (stopped);
}

int	error_exit(char *msg)
{
	int	len;

	len = 0;
	while (msg[len])
		len++;
	write(2, msg, len);
	return (1);
}
