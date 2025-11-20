#include "push_swap.h"
#include <stdlib.h>

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

static int	parse_single_arg(t_ps *ps, char *arg)
{
	char	**tokens;
	int		*vals;
	int		count;
	int		i;

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
	{
		ps_free_split(tokens);
		return (0);
	}
	i = 0;
	while (i < count)
	{
		if (!ft_atoi(tokens[i], &vals[i]))
			return (free(vals), ps_free_split(tokens), 0);
		i++;
	}
	ps_free_split(tokens);
	return (fill_stack_and_check(ps, vals, count));
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
		if (!ft_atoi(argv[i], &vals[i - 1]))
		{
			free(vals);
			return (0);
		}
		i++;
	}
	return (fill_stack_and_check(ps, vals, argc - 1));
}

int	parse_args(t_ps *ps, int argc, char **argv)
{
	if (argc == 2)
		return (parse_single_arg(ps, argv[1]));
	else
		return (parse_multi_args(ps, argc, argv));
}
