/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:20:00 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/14 09:58:08 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map.h"
#include "../../include/utils.h"

static const char	*check_rectangular(const t_map *m)
{
	size_t	r;

	r = -1;
	while (++r < m->rows)
	{
		if (ft_strlen(m->grid[r]) != m->cols)
			return ("Row length mismatch (not rectangular)");
	}
	return (NULL);
}

static void	count_tile(t_map *m, int tile, size_t row, size_t col)
{
	if (tile == t_player)
	{
		m->count_p++;
		m->px = col;
		m->py = row;
	}
	else if (tile == t_exit)
		m->count_e++;
	else if (tile == t_col)
		m->count_c++;
}

static const char	*fill_tiles_and_count(t_map *map)
{
	size_t		row;
	size_t		col;
	int			tile;
	const char	*error;

	map->count_p = 0;
	map->count_e = 0;
	map->count_c = 0;
	row = -1;
	while (++row < map->rows)
	{
		col = -1;
		while (++col < map->cols)
		{
			error = NULL;
			tile = tile_from_char(map->grid[row][col], &error);
			if (error)
				return (error);
			map->tiles[row][col] = tile;
			count_tile(map, tile, row, col);
		}
	}
	return (NULL);
}

static const char	*check_pec_counts(const t_map *m)
{
	if (m->count_p != 1)
		return ("Need exactly 1 player");
	if (m->count_e != 1)
		return ("Need exactly 1 exit");
	if (m->count_c < 1)
		return ("Need at least 1 collectible");
	return (NULL);
}

const char	*validate_map(t_map *m)
{
	const char	*err;

	err = check_rectangular(m);
	if (err)
		return (err);
	err = alloc_tiles(m);
	if (err)
		return (err);
	err = fill_tiles_and_count(m);
	if (err)
		return (err);
	err = check_pec_counts(m);
	if (err)
		return (err);
	err = check_outer_walls(m);
	if (err)
		return (err);
	return (NULL);
}
