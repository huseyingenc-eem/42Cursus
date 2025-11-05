/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:26:45 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/05 16:25:29 by hgenc            ###   ########.fr       */
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

/* map */
typedef struct s_map
{
	char	**grid;
	int	**tiles;
	size_t	rows;
	size_t	cols;
	int		count_p;
	int		count_e;
	int		count_c;
	int		px;
	int		py;
}	t_map;

/* map_load.c */
const char	*load_map(const char *path, t_map *m);
/* map_validate.c */
const char	*validate_map(t_map *m);
/* path_check.c */
const char	*validate_map_reachable(const t_map *m);


void	path_enqueue_neighbors(const t_map *m, int **vis,
			t_point *queue, int *rear, t_point cur);

#endif
