/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:38:10 by hgenc             #+#    #+#             */
/*   Updated: 2025/07/03 16:06:30 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

static int	ft_putunbr_len(unsigned int n)
{
	int	len;

	len = 0;
	if (n >= 10)
		len += ft_putunbr_len(n / 10);
	len += ft_putchar_len((n % 10) + '0');
	return (len);
}

static int	ft_formats(va_list *args, const char format)
{
	int	len;

	len = 0;
	if (format == 'c')
		len += ft_putchar_len(va_arg(*args, int));
	else if (format == 's')
		len += ft_putstr_len(va_arg(*args, char *));
	else if (format == 'p')
		len += ft_putptr_len((unsigned long long)va_arg(*args, void *));
	else if (format == 'd' || format == 'i')
		len += ft_putnbr_len(va_arg(*args, int));
	else if (format == 'u')
		len += ft_putunbr_len(va_arg(*args, unsigned int));
	else if (format == 'x')
		len += ft_puthex_len((unsigned long)va_arg(*args, unsigned int), 0);
	else if (format == 'X')
		len += ft_puthex_len((unsigned long)va_arg(*args, unsigned int), 1);
	else if (format == '%')
		len += ft_putchar_len('%');
	else
	{
		len += ft_putchar_len('%');
		len += ft_putchar_len(format);
	}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		total_len;

	if (!format)
		return (-1);
	i = 0;
	total_len = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (format[i + 1])
			{
				total_len += ft_formats(&args, format[i + 1]);
				i++;
			}
		}
		else
			total_len += ft_putchar_len(format[i]);
		i++;
	}
	va_end(args);
	return (total_len);
}
