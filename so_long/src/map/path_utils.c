/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:05:00 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/05 14:41:42 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map.h"

static int	is_valid_move(const t_map *m, int **vis, int ny, int nx)
{
	if (ny < 0 || nx < 0)
		return (0);
	if (ny >= (int)m->rows || nx >= (int)m->cols)
		return (0);
	if (vis[ny][nx])
		return (0);
	if (m->tiles[ny][nx] == T_WALL)
		return (0);
	return (1);
}

void	path_enqueue_neighbors(const t_map *m, int **vis,
			t_point *queue, int *rear, t_point cur)
{
	static const int	dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	int					d;
	int					ny;
	int					nx;

	d = -1;
	while (++d < 4)
	{
		ny = cur.y + dirs[d][0];
		nx = cur.x + dirs[d][1];
		if (is_valid_move(m, vis, ny, nx))
		{
			vis[ny][nx] = 1;
			queue[*rear] = (t_point){ny, nx};
			(*rear)++;
		}
	}
}
