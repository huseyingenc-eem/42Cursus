/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:49:44 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/10 15:57:49 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_four(t_ps *ps)
{
	int	min_pos;

	min_pos = find_min_pos(ps->a);
	if (min_pos == 1)
		sa(ps);
	else if (min_pos == 2)
	{
		rra(ps);
		rra(ps);
	}
	else if (min_pos == 3)
		rra(ps);
	pb(ps);
	sort_three(ps);
	pa(ps);
}

static void	sort_five(t_ps *ps)
{
	int	min_pos;

	min_pos = find_min_pos(ps->a);
	if (min_pos == 1)
		sa(ps);
	else if (min_pos == 2)
	{
		ra(ps);
		ra(ps);
	}
	else if (min_pos == 3)
	{
		rra(ps);
		rra(ps);
	}
	else if (min_pos == 4)
		rra(ps);
	pb(ps);
	sort_four(ps);
	pa(ps);
}

void	sort_small(t_ps *ps)
{
	if (ps->size_a == 2)
		sort_two(ps);
	else if (ps->size_a == 3)
		sort_three(ps);
	else if (ps->size_a == 4)
		sort_four(ps);
	else if (ps->size_a == 5)
		sort_five(ps);
}
