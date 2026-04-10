/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:42:48 by hgenc@stude       #+#    #+#             */
/*   Updated: 2025/11/22 18:20:28 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>

# define INT_MINN -2147483648
# define INT_MAXX 2147483647
# define TRUE 1
# define FALSE 0

typedef struct s_node
{
	int				val;
	int				idx;
	struct s_node	*prev;
	struct s_node	*next;
}					t_node;

typedef struct s_ps
{
	t_node			*a;
	t_node			*b;
	int				size_a;
	int				size_b;
}					t_ps;

size_t				ft_strlen(const char *s);
void				ft_putstr_fd(const char *s, int fd);
char				*ft_strdup(const char *s);
char				*ft_strjoin(const char *s1, const char *s2);

int					ft_is_space(char c);
int					ft_is_digit(char c);
int					ft_atoi(const char *s, int *out);

int					ft_is_sorted(t_node *top);
void				free_all(t_ps *ps);
void				error_exit(t_ps *ps);

int					parse_args(t_ps *ps, int argc, char **argv);

void				ps_free_split(char **arr);
char				**ps_split_ws(const char *s);
void				ps_free_split(char **arr);
int					has_duplicate(int *vals, int count);

void				normalize_indices(t_ps *ps);

t_node				*new_node(int val);
void				push_front(t_node **top, t_node *n);
void				push_back(t_node **top, t_node *n);

void				sa(t_ps *ps);
void				sb(t_ps *ps);
void				ss(t_ps *ps);

void				pa(t_ps *ps);
void				pb(t_ps *ps);

void				ra(t_ps *ps);
void				rb(t_ps *ps);
void				rr(t_ps *ps);

void				rra(t_ps *ps);
void				rrb(t_ps *ps);
void				rrr(t_ps *ps);

void				sort_small(t_ps *ps);

void				solve_radix(t_ps *ps);

#endif
