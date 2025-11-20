/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_reverse_rotate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:48:10 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/10 15:53:08 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	do_reverse_rotate(t_node **stack)
{
	t_node	*last;
	t_node	*second_last;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	last = *stack;
	while (last->next)
		last = last->next;
	second_last = last->prev;
	second_last->next = NULL;
	last->prev = NULL;
	push_front(stack, last);
}

void	rra(t_ps *ps)
{
	do_reverse_rotate(&ps->a);
	ft_putstr_fd("rra\n", 1);
}

void	rrb(t_ps *ps)
{
	do_reverse_rotate(&ps->b);
	ft_putstr_fd("rrb\n", 1);
}

void	rrr(t_ps *ps)
{
	do_reverse_rotate(&ps->a);
	do_reverse_rotate(&ps->b);
	ft_putstr_fd("rrr\n", 1);
}
