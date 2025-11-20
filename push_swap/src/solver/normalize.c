/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:48:07 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/10 15:48:09 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

static void	copy_values(t_node *top, int *arr, int size)
{
	int	i;

	i = -1;
	while (++i < size && top)
	{
		arr[i] = top->val;
		top = top->next;
	}
}

static void	sort_array(int *arr, int size)
{
	int	i;
	int	j;
	int	tmp;

	i = -1;
	while (++i < size - 1)
	{
		j = i;
		while (++j < size)
		{
			if (arr[i] > arr[j])
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}

static int	find_index(int *sorted, int size, int val)
{
	int	i;

	i = -1;
	while (++i < size)
		if (sorted[i] == val)
			return (i);
	return (0);
}

void	normalize_indices(t_ps *ps)
{
	int		*sorted;
	t_node	*cur;

	if (!ps || !ps->a || ps->size_a <= 0)
		return ;
	sorted = (int *)malloc(sizeof(int) * ps->size_a);
	if (!sorted)
		return ;
	copy_values(ps->a, sorted, ps->size_a);
	sort_array(sorted, ps->size_a);
	cur = ps->a;
	while (cur)
	{
		cur->idx = find_index(sorted, ps->size_a, cur->val);
		cur = cur->next;
	}
	free(sorted);
}
