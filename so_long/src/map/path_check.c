/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 00:00:00 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/05 16:25:29 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map.h"
#include "../../include/utils.h"
#include <stdlib.h>

#ifndef MAX_DIM
# define MAX_DIM 2000
#endif
#ifndef MAX_QUEUE
# define MAX_QUEUE 1000000
#endif

/* -- 1/5 -- */
static void	init_visited_row(int *row, size_t cols)
{
	size_t	i;

	i = -1;
	while (++i < cols)
		row[i] = FALSE;
}

/* -- 2/5 -- */
static int	**alloc_visited(size_t rows, size_t cols)
{
	int	**vis;
	size_t	r;

	if (rows > MAX_DIM || cols > MAX_DIM)
		return (NULL);
	vis = (int **)malloc(sizeof(int *) * rows);
	if (!vis)
		return (NULL);
	r = -1;
	while (++r < rows)
	{
		vis[r] = (int *)malloc(sizeof(int) * cols);
		if (!vis[r])
		{
			while (r > 0)
			{
				r--;
				free(vis[r]);
			}
			free(vis);
			return (NULL);
		}
		init_visited_row(vis[r], cols);
	}
	return (vis);
}

static void	free_visited(int **vis, size_t rows)
{
	size_t	r;

	if (!vis)
		return ;
	r = -1;
	while (++r < rows)
		free(vis[r]);
	free(vis);
}


static int	bfs_search(const t_map *m, int **vis, t_point *queue)
{
	int	front;
	int	rear;
	int	collected;
	int	exit_found;
	t_point	cur;

	front = 0;
	rear = 0;
	collected = 0;
	exit_found = FALSE;
	queue[rear++] = (t_point){m->py, m->px};
	vis[m->py][m->px] = TRUE;
	while (front < rear)
	{
		cur = queue[front++];
		if (m->tiles[cur.y][cur.x] == T_COL)
			collected++;
		if (m->tiles[cur.y][cur.x] == T_EXIT)
			exit_found = TRUE;
		path_enqueue_neighbors(m, vis, queue, &rear, cur);
	}
	ft_printf("Path check: %d/%d collectibles, exit=%s\n",
		collected, m->count_c, exit_found ? "yes" : "no");
	return (collected == m->count_c && exit_found);
}

/* -- 5/5 (public) -- */
const char	*validate_map_reachable(const t_map *m)
{
	int			**vis;
	t_point		*queue;
	size_t		qsz;
	int			ok;

	ft_printf("Pathfinding for %zu x %zu map...\n", m->rows, m->cols);
	qsz = m->rows * m->cols;
	if (qsz > MAX_QUEUE)
		return ("Map too large for pathfinding");
	vis = alloc_visited(m->rows, m->cols);
	if (!vis)
		return ("Cannot allocate visited array");
	queue = (t_point *)malloc(sizeof(t_point) * qsz);
	if (!queue)
	{
		free_visited(vis, m->rows);
		return ("Cannot allocate queue");
	}
	ok = bfs_search(m, vis, queue);
	free(queue);
	free_visited(vis, m->rows);
	if (!ok)
		return ("Player cannot reach all collectibles or exit");
	return (NULL);
}
