#include "push_swap.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_ps	ps;

	if (argc < 2)
		return (0);
	ps.a = NULL;
	ps.b = NULL;
	ps.size_a = 0;
	ps.size_b = 0;
	if (!parse_args(&ps, argc, argv))
		error_exit(&ps);
	if (ps.size_a == 1 || is_sorted(ps.a))
	{
		free_all(&ps);
		return (0);
	}
	if (ps.size_a <= 5)
		sort_small(&ps);
	else
	{
		normalize_indices(&ps);
		solve_radix(&ps);
	}
	free_all(&ps);
	return (0);
}
