/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:48:10 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/10 15:53:08 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>

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
