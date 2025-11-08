#include "push_swap.h"
#include <unistd.h>

size_t	ps_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ps_putstr_fd(const char *s, int fd)
{
	if (!s)
		return ;
	(void)write(fd, s, ps_strlen(s));
}


int	ps_is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	ps_is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ps_atoi_safe(const char *s, int *out)
{
	long long	sign;
	long long	acc;
	int			digits;

	if (!s || !out)
		return (0);
	while (ps_is_space(*s))
		++s;
	sign = 1;
	if (*s == '+' || *s == '-')
		sign = (*s++ == '-') ? -1LL : 1LL;
	acc = 0;
	digits = 0;
	while (ps_is_digit(*s))
	{
		acc = acc * 10 + (*s - '0');
		digits = 1;
		++s;
	}
	while (ps_is_space(*s))
		++s;
	if (!digits || *s != '\0')
		return (0);
	if (sign * acc > (long long)INT_MAX || sign * acc < (long long)INT_MIN)
		return (0);
	*out = (int)(sign * acc);
	return (1);
}

int	is_sorted(t_node *top)
{
	if (!top)
		return (1);
	while (top->next)
	{
		if (top->val > top->next->val)
			return (0);
		top = top->next;
	}
	return (1);
}
