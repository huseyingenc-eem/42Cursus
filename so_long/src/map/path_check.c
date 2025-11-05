/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 00:00:00 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/05 16:59:17 by hgenc            ###   ########.fr       */
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

static void	init_visited_row(int *row, size_t cols)
{
	size_t	i;

	i = -1;
	while (++i < cols)
		row[i] = FALSE;
}

static int	**alloc_visited(size_t rows, size_t cols)
{
	int		**vis;
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

static int	bfs_search(t_bfs_ctx *ctx, const t_map *m)
{
	int		front;
	int		collected;
	int		exit_found;
	t_point	cur;

	front = 0;
	collected = 0;
	exit_found = FALSE;
	ctx->queue[ctx->rear++] = (t_point){m->py, m->px};
	ctx->visited[m->py][m->px] = TRUE;
	while (front < ctx->rear)
	{
		cur = ctx->queue[front++];
		if (m->tiles[cur.y][cur.x] == T_COL)
			collected++;
		if (m->tiles[cur.y][cur.x] == T_EXIT)
			exit_found = TRUE;
		path_enqueue_neighbors(ctx, cur);
	}
	return (collected == m->count_c && exit_found);
}

const char	*validate_map_reachable(const t_map *m)
{
	t_bfs_ctx	ctx;
	size_t		qsz;
	int			ok;

	qsz = m->rows * m->cols;
	if (qsz > MAX_QUEUE)
		return ("Map too large for pathfinding");
	ctx.visited = alloc_visited(m->rows, m->cols);
	if (!ctx.visited)
		return ("Cannot allocate visited array");
	ctx.queue = (t_point *)malloc(sizeof(t_point) * qsz);
	if (!ctx.queue)
	{
		free_visited(ctx.visited, m->rows);
		return ("Cannot allocate queue");
	}
	ctx.map = m;
	ctx.rear = 0;
	ok = bfs_search(&ctx, m);
	free(ctx.queue);
	free_visited(ctx.visited, m->rows);
	if (!ok)
		return ("Player cannot reach all collectibles or exit");
	return (NULL);
}
