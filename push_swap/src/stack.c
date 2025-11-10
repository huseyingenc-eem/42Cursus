/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:49:35 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/10 15:49:39 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

t_node	*ps_new_node(int val)
{
	t_node	*n;

	n = (t_node *)malloc(sizeof(t_node));
	if (!n)
		return (NULL);
	n->val = val;
	n->idx = 0;
	n->prev = NULL;
	n->next = NULL;
	return (n);
}

void	ps_push_front(t_node **top, t_node *n)
{
	if (!n)
		return ;
	n->next = *top;
	n->prev = NULL;
	if (*top)
		(*top)->prev = n;
	*top = n;
}

void	ps_push_back(t_node **top, t_node *n)
{
	t_node	*cur;

	if (!n)
		return ;
	if (!*top)
	{
		*top = n;
		n->prev = NULL;
		n->next = NULL;
		return ;
	}
	cur = *top;
	while (cur->next)
		cur = cur->next;
	cur->next = n;
	n->prev = cur;
	n->next = NULL;
}

int	ps_stack_size(t_node *top)
{
	int	count;

	count = 0;
	while (top)
	{
		count++;
		top = top->next;
	}
	return (count);
}
