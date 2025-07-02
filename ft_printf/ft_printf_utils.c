
#include <unistd.h>
#include "ft_printf.h"
#include <stdlib.h>

int	ft_putchar_len(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_putstr_len(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (str[len])
	{
		ft_putchar_len(str[len]); // Kendi fonksiyonun!
		len++;
	}
	return (len);
}

int	ft_puthex_len(unsigned long long n, int is_upper)
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

int	ft_putptr_len(unsigned long long ptr)
{
	int	len;

	len = 0;
	if (ptr == 0)
		return (write(1, "(null)", 6));
	len += ft_putstr_len("0x");
	len += ft_puthex_len(ptr, 0);
	return (len);
}

int	ft_putnbr_len(int n)
{
	char	*s;
	int		len;

	s = ft_itoa(n);
	len = ft_putstr_len(s);
	free(s);
	return (len);
}