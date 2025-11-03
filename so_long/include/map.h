/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:26:45 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/03 17:26:57 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

typedef enum e_tile
{
	T_WALL = 0,
	T_EMPTY = 1,
	T_COL = 2,
	T_EXIT = 3,
	T_PLAYER = 4
}			t_tile;

typedef struct s_map
{
	char	**grid;
	uint8_t	**tiles;
	size_t	rows;
	size_t	cols;
	int		count_p;
	int		count_e;
	int		count_c;
	int px, py;
}			t_map;

/* map_load.c */
bool		load_map(const char *path, t_map *m);

/* map_validate.c */
bool		validate_map(t_map *m);

/* path_check.c */
bool		validate_map_reachable(const t_map *m);

/* map_free.c */
void		free_map(t_map *m);

#endif