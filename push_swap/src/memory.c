#include "push_swap.h"
#include <stdlib.h>
#include <unistd.h>

static void	free_stack(t_node **top)
{
	t_node	*cur;
	t_node	*nx;

	if (!top || !*top)
		return ;
	cur = *top;
	while (cur)
	{
		nx = cur->next;
		free(cur);
		cur = nx;
	}
	*top = NULL;
}

void	free_all(t_ps *ps)
{
	if (!ps)
		return ;
	free_stack(&ps->a);
	free_stack(&ps->b);
}

void	error_exit(t_ps *ps)
{
	free_all(ps);
	ps_putstr_fd("Error\n", 2);
	exit(1);
}   
