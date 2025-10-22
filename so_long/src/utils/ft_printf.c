#include "../../include/utils.h"
#include <unistd.h>

static int	ft_putchar(char c)
{
    return (write(1, &c, 1));
}

static int	ft_putstr(char *s)
{
    int	i;

    if (!s)
        s = "(null)";
    i = 0;
    while (s[i])
        i += ft_putchar(s[i]);
    return (i);
}

static int	ft_putnbr(long n)
{
    int	len;

    len = 0;
    if (n < 0)
    {
        len += ft_putchar('-');
        n = -n;
    }
    if (n >= 10)
        len += ft_putnbr(n / 10);
    len += ft_putchar((n % 10) + '0');
    return (len);
}

static int	ft_handle(va_list args, char c)
{
    if (c == 'c')
        return (ft_putchar(va_arg(args, int)));
    if (c == 's')
        return (ft_putstr(va_arg(args, char *)));
    if (c == 'd' || c == 'i')
        return (ft_putnbr(va_arg(args, int)));
    if (c == '%')
        return (ft_putchar('%'));
    return (0);
}

int	ft_printf(const char *format, ...)
{
    va_list	args;
    int		count;
    int		i;

    if (!format)
        return (-1);
    va_start(args, format);
    count = 0;
    i = 0;
    while (format[i])
    {
        if (format[i] == '%' && format[i + 1])
        {
            i++;
            count += ft_handle(args, format[i]);
        }
        else
            count += ft_putchar(format[i]);
        i++;
    }
    va_end(args);
    return (count);
}
