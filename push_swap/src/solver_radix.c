#include "push_swap.h"

static int	get_max_bits(int max_num)
{
	int	bits;

	bits = 0;
	while ((max_num >> bits) != 0)
		bits++;
	return (bits);
}

void	solve_radix(t_ps *ps)
{
	int	max_bits;
	int	i;
	int	j;
	int	size;

	max_bits = get_max_bits(ps->size_a - 1);
	i = 0;
	while (i < max_bits)
	{
		size = ps->size_a;
		j = 0;
		while (j < size)
		{
			if (((ps->a->idx >> i) & 1) == 1)
				ra(ps);
			else
				pb(ps);
			j++;
		}
		while (ps->size_b > 0)
			pa(ps);
		i++;
	}
}
