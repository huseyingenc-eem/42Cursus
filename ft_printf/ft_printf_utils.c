/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:38:16 by hgenc             #+#    #+#             */
/*   Updated: 2025/07/03 16:09:24 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_putchar_len(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr_len(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (str[len])
		len++;
	write(1, str, len);
	return (len);
}

int	ft_puthex_len(unsigned long n, int is_upper)
{
	char	*base;
	int		len;

	len = 0;
	if (is_upper)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (n >= 16)
		len += ft_puthex_len(n / 16, is_upper);
	len += ft_putchar_len(base[n % 16]);
	return (len);
}

int	ft_putptr_len(unsigned long ptr)
{
	int	len;

	len = 0;
	if (ptr == 0)
		return (write(1, "(nil)", 5));
	len += ft_putstr_len("0x");
	len += ft_puthex_len(ptr, 0);
	return (len);
}

int	ft_putnbr_len(int n)
{
	int				len;
	unsigned int	num;

	len = 0;
	if (n < 0)
	{
		len += ft_putchar_len('-');
		num = -n;
	}
	else
		num = n;
	if (num >= 10)
		len += ft_putnbr_len(num / 10);
	len += ft_putchar_len((num % 10) + '0');
	return (len);
}
