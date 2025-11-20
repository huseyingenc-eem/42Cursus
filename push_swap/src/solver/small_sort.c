/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:49:44 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/19 14:30:00 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_three(t_ps *ps)
{
	int	a;
	int	b;
	int	c;

	if (ft_is_sorted(ps->a))
		return ;
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

static int	find_min_pos(t_node *top, int size)
{
	int		min_val;
	int		min_pos;
	int		pos;
	t_node	*cur;

	if (!top)
		return (-1);
	min_val = top->val;
	min_pos = 0;
	pos = 0;
	cur = top;
	while (cur && pos < size)
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

static void	push_all_save_three(t_ps *ps)
{
	int	min_pos;
	int	current_size;

	current_size = ps->size_a;
	while (current_size > 3)
	{
		min_pos = find_min_pos(ps->a, current_size);
		if (min_pos <= current_size / 2)
			while (min_pos-- > 0)
				ra(ps);
		else
			while (min_pos++ < current_size)
				rra(ps);
		pb(ps);
		current_size--;
	}
}

void	sort_small(t_ps *ps)
{
	if (ft_is_sorted(ps->a))
		return ;
	if (ps->size_a == 2)
	{
		if (ps->a->val > ps->a->next->val)
			sa(ps);
		return ;
	}
	if (ps->size_a == 3)
	{
		sort_three(ps);
		return ;
	}
	push_all_save_three(ps);
	sort_three(ps);
	while (ps->size_b > 0)
		pa(ps);
}
