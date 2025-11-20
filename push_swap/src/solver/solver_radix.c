/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_radix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:49:41 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/10 15:49:42 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			if (((ps->a->idx >> i) & 1) == 0)
				pb(ps);
			else
				ra(ps);
			j++;
		}
		while (ps->size_b > 0)
			pa(ps);
		i++;
	}
}
