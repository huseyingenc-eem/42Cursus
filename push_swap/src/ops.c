#include "push_swap.h"
#include <unistd.h>

static void	do_swap(t_node **top)
{
	t_node	*first;
	t_node	*second;

	if (!top || !*top || !(*top)->next)
		return ;
	first = *top;
	second = first->next;
	first->next = second->next;
	if (second->next)
		second->next->prev = first;
	second->prev = NULL;
	second->next = first;
	first->prev = second;
	*top = second;
}

void	sa(t_ps *ps)
{
	do_swap(&ps->a);
	ps_putstr_fd("sa\n", 1);
}

void	sb(t_ps *ps)
{
	do_swap(&ps->b);
	ps_putstr_fd("sb\n", 1);
}

void	ss(t_ps *ps)
{
	do_swap(&ps->a);
	do_swap(&ps->b);
	ps_putstr_fd("ss\n", 1);
}

static void	do_push(t_node **from, t_node **to)
{
	t_node	*tmp;

	if (!from || !*from)
		return ;
	tmp = *from;
	*from = (*from)->next;
	if (*from)
		(*from)->prev = NULL;
	tmp->next = *to;
	tmp->prev = NULL;
	if (*to)
		(*to)->prev = tmp;
	*to = tmp;
}

void	pa(t_ps *ps)
{
	do_push(&ps->b, &ps->a);
	ps->size_b--;
	ps->size_a++;
	ps_putstr_fd("pa\n", 1);
}

void	pb(t_ps *ps)
{
	do_push(&ps->a, &ps->b);
	ps->size_a--;
	ps->size_b++;
	ps_putstr_fd("pb\n", 1);
}

static void	do_rotate(t_node **top)
{
	t_node	*first;
	t_node	*last;

	if (!top || !*top || !(*top)->next)
		return ;
	first = *top;
	last = *top;
	while (last->next)
		last = last->next;
	*top = first->next;
	(*top)->prev = NULL;
	last->next = first;
	first->prev = last;
	first->next = NULL;
}

void	ra(t_ps *ps)
{
	do_rotate(&ps->a);
	ps_putstr_fd("ra\n", 1);
}

void	rb(t_ps *ps)
{
	do_rotate(&ps->b);
	ps_putstr_fd("rb\n", 1);
}

void	rr(t_ps *ps)
{
	do_rotate(&ps->a);
	do_rotate(&ps->b);
	ps_putstr_fd("rr\n", 1);
}

static void	do_reverse_rotate(t_node **top)
{
	t_node	*last;
	t_node	*second_last;

	if (!top || !*top || !(*top)->next)
		return ;
	last = *top;
	while (last->next)
		last = last->next;
	second_last = last->prev;
	second_last->next = NULL;
	last->prev = NULL;
	last->next = *top;
	(*top)->prev = last;
	*top = last;
}

void	rra(t_ps *ps)
{
	do_reverse_rotate(&ps->a);
	ps_putstr_fd("rra\n", 1);
}

void	rrb(t_ps *ps)
{
	do_reverse_rotate(&ps->b);
	ps_putstr_fd("rrb\n", 1);
}

void	rrr(t_ps *ps)
{
	do_reverse_rotate(&ps->a);
	do_reverse_rotate(&ps->b);
	ps_putstr_fd("rrr\n", 1);
}
