/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 21:11:51 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/22 12:46:06 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

int	ft_atoi_bonus(const char *str)
{
	long		result;
	int			sign;
	const long	int_max = 2147483647;
	const long	int_min = -2147483648;

	result = 0;
	sign = 1;
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
		if (sign == 1 && result > int_max)
			return (0);
		if (sign == -1 && (-result < int_min))
			return (0);
		str++;
	}
	return ((int)result * sign);
}

void	ft_putchar_fd_bonus(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd_bonus(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		ft_putchar_fd_bonus(*s, fd);
		s++;
	}
}

void	ft_error_exit_bonus(char *msg)
{
	ft_putstr_fd_bonus("Error\n", 2);
	ft_putstr_fd_bonus(msg, 2);
	ft_putstr_fd_bonus("\n", 2);
	exit(1);
}

void	ft_putnbr_fd_bonus(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putstr_fd_bonus("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd_bonus('-', fd);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_fd_bonus(n / 10, fd);
	ft_putchar_fd_bonus((n % 10) + '0', fd);
}
