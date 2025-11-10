/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:42:48 by hgenc@stude       #+#    #+#             */
/*   Updated: 2025/11/10 15:57:47 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <limits.h>

typedef struct s_node
{
	int				val;
	int				idx;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct s_ps
{
	t_node	*a;
	t_node	*b;
	int		size_a;
	int		size_b;
}	t_ps;

size_t	ps_strlen(const char *s);
void	ps_putstr_fd(const char *s, int fd);

int		ps_is_space(char c);
int		ps_is_digit(char c);

int		ps_atoi_safe(const char *s, int *out);

int		is_sorted(t_node *top);
void	free_all(t_ps *ps);
void	error_exit(t_ps *ps);

int		parse_args(t_ps *ps, int argc, char **argv);

char	**ps_split_ws(const char *s);
void	ps_free_split(char **arr);
int		has_duplicate(int *vals, int count);

void	normalize_indices(t_ps *ps);

t_node	*ps_new_node(int val);
void	ps_push_front(t_node **top, t_node *n);
void	ps_push_back(t_node **top, t_node *n);
int		ps_stack_size(t_node *top);

void	sa(t_ps *ps);
void	sb(t_ps *ps);
void	ss(t_ps *ps);

void	pa(t_ps *ps);
void	pb(t_ps *ps);

void	ra(t_ps *ps);
void	rb(t_ps *ps);
void	rr(t_ps *ps);

void	rra(t_ps *ps);
void	rrb(t_ps *ps);
void	rrr(t_ps *ps);

void	sort_small(t_ps *ps);
void	sort_two(t_ps *ps);
void	sort_three(t_ps *ps);
int		find_min_pos(t_node *top);

void	solve_radix(t_ps *ps);

#endif
