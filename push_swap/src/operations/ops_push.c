/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:48:10 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/10 15:53:07 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	do_push(t_node **from, t_node **to)
{
	t_node	*node_to_push;

	if (!from || !*from)
		return ;
	node_to_push = *from;
	*from = (*from)->next;
	if (*from)
		(*from)->prev = NULL;
	push_front(to, node_to_push);
}

void	pa(t_ps *ps)
{
	if (ps->size_b > 0)
	{
		do_push(&ps->b, &ps->a);
		ps->size_a++;
		ps->size_b--;
		ft_putstr_fd("pa\n", 1);
	}
}

void	pb(t_ps *ps)
{
	if (ps->size_a > 0)
	{
		do_push(&ps->a, &ps->b);
		ps->size_b++;
		ps->size_a--;
		ft_putstr_fd("pb\n", 1);
	}
}
