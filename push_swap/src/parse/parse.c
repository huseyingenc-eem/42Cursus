/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 18:04:11 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/22 18:19:50 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

static char	*join_args(int argc, char **argv)
{
	char	*str;
	char	*tmp;
	int		i;

	str = ft_strdup("");
	if (!str)
		return (NULL);
	i = 0;
	while (++i < argc)
	{
		tmp = ft_strjoin(str, argv[i]);
		free(str);
		if (!tmp)
			return (NULL);
		str = tmp;
		if (i < argc - 1)
		{
			tmp = ft_strjoin(str, " ");
			free(str);
			if (!tmp)
				return (NULL);
			str = tmp;
		}
	}
	return (str);
}

static int	fill_stack_and_check(t_ps *ps, int *vals, int count)
{
	int	i;

	if (has_duplicate(vals, count))
	{
		free(vals);
		return (0);
	}
	i = 0;
	while (i < count)
	{
		push_back(&ps->a, new_node(vals[i]));
		i++;
	}
	ps->size_a = count;
	free(vals);
	return (1);
}

int	parse_args(t_ps *ps, int argc, char **argv)
{
	char	**tokens;
	int		*vals;
	int		count;
	int		i;
	char	*str;

	str = join_args(argc, argv);
	if (!str)
		return (0);
	tokens = ps_split_ws(str);
	free(str);
	if (!tokens || !tokens[0])
		return (ps_free_split(tokens), 0);
	count = 0;
	while (tokens[count])
		count++;
	vals = (int *)malloc(sizeof(int) * count);
	if (!vals)
		return (ps_free_split(tokens), 0);
	i = -1;
	while (++i < count)
		if (!ft_atoi(tokens[i], &vals[i]))
			return (free(vals), ps_free_split(tokens), 0);
	ps_free_split(tokens);
	return (fill_stack_and_check(ps, vals, count));
}
