/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:48:15 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/10 16:00:28 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

static int	parse_tokens_to_vals(char **tokens, int *vals, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (!ps_atoi_safe(tokens[i], &vals[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	fill_stack_from_vals(t_ps *ps, int *vals, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		ps_push_back(&ps->a, ps_new_node(vals[i]));
		i++;
	}
	ps->size_a = count;
	return (1);
}

static int	parse_single_arg(t_ps *ps, char *arg)
{
	char	**tokens;
	int		*vals;
	int		count;

	tokens = ps_split_ws(arg);
	if (!tokens || !tokens[0])
	{
		ps_free_split(tokens);
		return (0);
	}
	count = 0;
	while (tokens[count])
		count++;
	vals = (int *)malloc(sizeof(int) * count);
	if (!vals)
		return (ps_free_split(tokens), 0);
	if (!parse_tokens_to_vals(tokens, vals, count))
		return (free(vals), ps_free_split(tokens), 0);
	ps_free_split(tokens);
	if (has_duplicate(vals, count))
		return (free(vals), 0);
	fill_stack_from_vals(ps, vals, count);
	return (free(vals), 1);
}

static int	parse_multi_args(t_ps *ps, int argc, char **argv)
{
	int	*vals;
	int	i;

	vals = (int *)malloc(sizeof(int) * (argc - 1));
	if (!vals)
		return (0);
	i = 1;
	while (i < argc)
	{
		if (!ps_atoi_safe(argv[i], &vals[i - 1]))
			return (free(vals), 0);
		i++;
	}
	if (has_duplicate(vals, argc - 1))
		return (free(vals), 0);
	fill_stack_from_vals(ps, vals, argc - 1);
	return (free(vals), 1);
}

int	parse_args(t_ps *ps, int argc, char **argv)
{
	if (argc == 2)
		return (parse_single_arg(ps, argv[1]));
	else
		return (parse_multi_args(ps, argc, argv));
}
