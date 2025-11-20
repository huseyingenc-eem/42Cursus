/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_swap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:48:10 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/10 15:53:05 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	ft_putstr_fd("sa\n", 1);
}

void	sb(t_ps *ps)
{
	do_swap(&ps->b);
	ft_putstr_fd("sb\n", 1);
}

void	ss(t_ps *ps)
{
	do_swap(&ps->a);
	do_swap(&ps->b);
	ft_putstr_fd("ss\n", 1);
}
