#include "push_swap.h"

static void	sort_two(t_ps *ps)
{
	if (ps->a->val > ps->a->next->val)
		sa(ps);
}

static void	sort_three(t_ps *ps)
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

static int	find_min_pos(t_node *top)
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
