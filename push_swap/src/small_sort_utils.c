/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:49:44 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/10 15:57:48 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_two(t_ps *ps)
{
	if (ps->a->val > ps->a->next->val)
		sa(ps);
}

void	sort_three(t_ps *ps)
{
	int	a;
	int	b;
	int	c;

	a = ps->a->val;
	b = ps->a->next->val;
	c = ps->a->next->next->val;
	if (a > b && b < c && a < c)
		sa(ps);
	else if (a > b && b > c)
	{
		sa(ps);
		rra(ps);
	}
	else if (a > b && b < c && a > c)
		ra(ps);
	else if (a < b && b > c && a < c)
	{
		sa(ps);
		ra(ps);
	}
	else if (a < b && b > c && a > c)
		rra(ps);
}

int	find_min_pos(t_node *top)
{
	int		min_val;
	int		min_pos;
	int		pos;
	t_node	*cur;

	min_val = top->val;
	min_pos = 0;
	pos = 0;
	cur = top;
	while (cur)
	{
		if (cur->val < min_val)
		{
			min_val = cur->val;
			min_pos = pos;
		}
		pos++;
		cur = cur->next;
	}
	return (min_pos);
}
