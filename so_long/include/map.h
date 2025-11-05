/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:26:45 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/05 16:59:17 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <stddef.h>

typedef enum e_tile
{
	T_WALL = 0,
	T_EMPTY = 1,
	T_COL = 2,
	T_EXIT = 3,
	T_PLAYER = 4
}	t_tile;

typedef struct s_point
{
	int	y;
	int	x;
}	t_point;

typedef struct s_map
{
	char	**grid;
	int		**tiles;
	size_t	rows;
	size_t	cols;
	int		count_p;
	int		count_e;
	int		count_c;
	int		px;
	int		py;
}	t_map;

typedef struct s_bfs_ctx
{
	const t_map	*map;
	int			**visited;
	t_point		*queue;
	int			rear;
}	t_bfs_ctx;

const char	*load_map(const char *path, t_map *m);
const char	*validate_map(t_map *m);
const char	*validate_map_reachable(const t_map *m);
const char	*check_outer_walls(const t_map *m);
const char	*alloc_tiles(t_map *m);
int			tile_from_char(char ch, const char **err);
void		path_enqueue_neighbors(t_bfs_ctx *ctx, t_point cur);

#endif
