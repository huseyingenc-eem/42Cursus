/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 00:00:00 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/03 17:55:18 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map.h"
#include "../../include/utils.h"
#include <stdlib.h>

typedef struct s_point
{
	int		y;
	int		x;
}			t_point;

static void	init_visited_row(bool *row, size_t cols)
{
	size_t	i;

	i = 0;
	while (i < cols)
	{
		row[i] = false;
		i++;
	}
}

static bool	**alloc_visited(size_t rows, size_t cols)
{
	bool	**vis;
	size_t	r;

	if (rows > 2000 || cols > 2000)
		return (NULL);
	vis = malloc(sizeof(bool *) * rows);
	if (!vis)
		return (NULL);
	r = 0;
	while (r < rows)
		vis[r++] = NULL;
	r = 0;
	while (r < rows)
	{
		vis[r] = malloc(sizeof(bool) * cols);
		if (!vis[r])
		{
			while (r-- > 0)
				free(vis[r]);
			return (free(vis), NULL);
		}
		init_visited_row(vis[r], cols);
		r++;
	}
	return (vis);
}

static void	free_visited(bool **vis, size_t rows)
{
	size_t	r;

	if (!vis)
		return ;
	r = 0;
	while (r < rows)
		free(vis[r++]);
	free(vis);
}

static bool	is_valid_move(const t_map *m, bool **vis, int ny, int nx)
{
	if (ny < 0 || nx < 0 || ny >= (int)m->rows || nx >= (int)m->cols)
		return (false);
	if (vis[ny][nx])
		return (false);
	if (m->tiles[ny][nx] == T_WALL)
		return (false);
	return (true);
}

static void	process_neighbors(const t_map *m, bool **vis, t_point *queue,
		int *rear, t_point cur)
{
	int	dirs[4][2];
	int	d;
	int	ny;
	int	nx;

	dirs[0][0] = -1;
	dirs[0][1] = 0;
	dirs[1][0] = 1;
	dirs[1][1] = 0;
	dirs[2][0] = 0;
	dirs[2][1] = -1;
	dirs[3][0] = 0;
	dirs[3][1] = 1;
	d = 0;
	while (d < 4)
	{
		ny = cur.y + dirs[d][0];
		nx = cur.x + dirs[d][1];
		if (is_valid_move(m, vis, ny, nx))
		{
			vis[ny][nx] = true;
			queue[(*rear)++] = (t_point){ny, nx};
		}
		d++;
	}
}

static bool	bfs_search(const t_map *m, bool **vis, t_point *queue)
{
	int		front;
	int		rear;
	int		collected;
	bool	exit_found;
	t_point	cur;

	front = 0;
	rear = 0;
	collected = 0;
	exit_found = false;
	queue[rear++] = (t_point){m->py, m->px};
	vis[m->py][m->px] = true;
	while (front < rear)
	{
		cur = queue[front++];
		if (m->tiles[cur.y][cur.x] == T_COL)
			collected++;
		if (m->tiles[cur.y][cur.x] == T_EXIT)
			exit_found = true;
		process_neighbors(m, vis, queue, &rear, cur);
	}
	ft_printf("Path check: %d/%d collectibles, exit=%s\n", collected,
		m->count_c, exit_found ? "yes" : "no");
	return (collected == m->count_c && exit_found);
}

bool	validate_map_reachable(const t_map *m)
{
	bool **vis;
	t_point *queue;
	size_t queue_size;
	bool result;

	ft_printf("Pathfinding for %zu x %zu map...\n", m->rows, m->cols);
	queue_size = m->rows * m->cols;
	if (queue_size > 1000000)
		return (ft_printf("Error: Map too large\n"), false);
	vis = alloc_visited(m->rows, m->cols);
	if (!vis)
		return (ft_printf("Error: Cannot allocate visited\n"), false);
	queue = malloc(sizeof(t_point) * queue_size);
	if (!queue)
	{
		free_visited(vis, m->rows);
		return (ft_printf("Error: Cannot allocate queue\n"), false);
	}
	result = bfs_search(m, vis, queue);
	free(queue);
	free_visited(vis, m->rows);
	return (result);
}