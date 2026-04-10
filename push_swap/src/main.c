/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:48:12 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/10 15:48:14 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_ps	ps;

	ps.a = NULL;
	ps.b = NULL;
	ps.size_a = 0;
	ps.size_b = 0;
	if (argc < 2)
		error_exit(&ps);
	if (!parse_args(&ps, argc, argv))
		error_exit(&ps);
	if (ps.size_a == 1 || ft_is_sorted(ps.a))
	{
		free_all(&ps);
		return (0);
	}
	if (ps.size_a <= 20)
		sort_small(&ps);
	else
	{
		normalize_indices(&ps);
		solve_radix(&ps);
	}
	free_all(&ps);
	return (0);
}
