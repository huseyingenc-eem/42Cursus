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
#include <limits.h>

static int	parse_positive_int(const char *str, int *value)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i])
	{
		if (result > (INT_MAX - (str[i] - '0')) / 10)
			return (FALSE);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	*value = (int)result;
	return (TRUE);
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
	if (!parse_positive_int(av[1], &data->nb_philo)
		|| !parse_positive_int(av[2], &data->time_die)
		|| !parse_positive_int(av[3], &data->time_eat)
		|| !parse_positive_int(av[4], &data->time_sleep))
		return (error_exit("Error: invalid values\n"));
	data->nb_meals = -1;
	if (ac == 6 && !parse_positive_int(av[5], &data->nb_meals))
		return (error_exit("Error: invalid values\n"));
	if (validate_values(data))
		return (error_exit("Error: invalid values\n"));
	return (0);
}
