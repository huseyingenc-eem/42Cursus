/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 14:30:00 by hgenc             #+#    #+#             */
/*   Updated: 2026/02/10 14:30:00 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ft_atoi(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return ((int)(result * sign));
}

static int	is_valid_arg(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (FALSE);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	validate_values(t_data *data)
{
	if (data->nb_philo < 1)
		return (TRUE);
	if (data->time_die < 1)
		return (TRUE);
	if (data->time_eat < 1)
		return (TRUE);
	if (data->time_sleep < 1)
		return (TRUE);
	if (data->nb_meals == 0)
		return (TRUE);
	return (FALSE);
}

int	parse_args(t_data *data, int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (error_exit("Error: wrong argument count\n"));
	i = 0;
	while (++i < ac)
	{
		if (!is_valid_arg(av[i]))
			return (error_exit("Error: invalid argument\n"));
	}
	data->nb_philo = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	data->nb_meals = -1;
	if (ac == 6)
		data->nb_meals = ft_atoi(av[5]);
	if (validate_values(data))
		return (error_exit("Error: invalid values\n"));
	return (0);
}
