/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:07:43 by hgenc             #+#    #+#             */
/*   Updated: 2025/06/30 10:33:14 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_count_digits(int n)
{
	int			len;
	long long	temp_n;

	len = 0;
	if (n == 0)
		return (1);
	temp_n = n;
	if (temp_n < 0)
	{
		temp_n = -temp_n;
		len++;
	}
	while (temp_n > 0)
	{
		temp_n /= 10;
		len++;
	}
	return (len);
}

static void	ft_convert_to_string(long long n, char *ptr, int num_len)
{
	int	i;

	i = num_len - 1;
	if (n == 0)
	{
		ptr[0] = '0';
		return ;
	}
	if (n < 0)
	{
		ptr[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		ptr[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
}

char	*ft_itoa(int n)
{
	int			num_len;
	char		*ptr;
	long long	temp_n;

	num_len = ft_count_digits(n);
	ptr = (char *)malloc(sizeof(char) * (num_len + 1));
	if (ptr == NULL)
		return (NULL);
	ptr[num_len] = '\0';
	temp_n = n;
	ft_convert_to_string(temp_n, ptr, num_len);
	return (ptr);
}
