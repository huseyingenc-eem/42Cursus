/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:49:30 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/10 16:00:27 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr_fd(const char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

static int	parse_sign(const char **s, long long *sign)
{
	*sign = 1;
	if (**s == '+' || **s == '-')
	{
		if (**s == '-')
			*sign = -1LL;
		(*s)++;
	}
	return (1);
}

static int	parse_digits(const char **s, long long *acc)
{
	int	digits;

	*acc = 0;
	digits = 0;
	while (ft_is_digit(**s))
	{
		*acc = *acc * 10 + (**s - '0');
		digits = 1;
		(*s)++;
	}
	return (digits);
}

int	ft_atoi(const char *s, int *out)
{
	long long	sign;
	long long	acc;
	int			digits;

	if (!s || !out)
		return (0);
	while (ft_is_space(*s))
		s++;
	parse_sign(&s, &sign);
	digits = parse_digits(&s, &acc);
	while (ft_is_space(*s))
		s++;
	if (!digits || *s != '\0')
		return (0);
	if (sign * acc > (long long)INT_MAXX || sign * acc < (long long)INT_MINN)
		return (0);
	*out = (int)(sign * acc);
	return (1);
}
