/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:20:00 by hgenc             #+#    #+#             */
/*   Updated: 2025/10/28 16:08:50 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map.h"
#include "../../include/utils.h"
#include <stdlib.h>

static uint8_t	tile_from_char(char ch)
{
	if (ch == '1')
		return (T_WALL);
	if (ch == '0')
		return (T_EMPTY);
	if (ch == 'C')
		return (T_COL);
	if (ch == 'E')
		return (T_EXIT);
	if (ch == 'P')
		return (T_PLAYER);
	error_exit("Invalid character in map");
	return (T_WALL);
}

static void	alloc_tiles(t_map *m)
{
	size_t	r;
	size_t	i;

	if (m->rows > 2000 || m->cols > 2000)
		error_exit("Map too large");
	m->tiles = (uint8_t **)malloc(sizeof(uint8_t *) * m->rows);
	if (!m->tiles)
		error_exit("Allocation failed (tiles)");
	r = 0;
	while (r < m->rows)
	{
		m->tiles[r] = NULL;
		r++;
	}
	r = 0;
	while (r < m->rows)
	{
		m->tiles[r] = (uint8_t *)malloc(sizeof(uint8_t) * m->cols);
		if (!m->tiles[r])
		{
			i = 0;
			while (i < r)
			{
				free(m->tiles[i]);
				m->tiles[i] = NULL;
				i++;
			}
			free(m->tiles);
			m->tiles = NULL;
			error_exit("Allocation failed (tiles rows)");
		}
		r++;
	}
}

static void	check_rectangular(const t_map *m)
{
	size_t	r;

	r = 0;
	while (r < m->rows)
	{
		if (ft_strlen(m->grid[r]) != m->cols)
			error_exit("Row length mismatch (not rectangular)");
		r++;
	}
}

static void	check_outer_walls(const t_map *m)
{
	size_t	c;
	size_t	r;

	c = 0;
	while (c < m->cols)
	{
		if (m->tiles[0][c] != T_WALL
			|| m->tiles[m->rows - 1][c] != T_WALL)
			error_exit("Map must be surrounded by walls (top/bottom)");
		c++;
	}
	r = 0;
	while (r < m->rows)
	{
		if (m->tiles[r][0] != T_WALL
			|| m->tiles[r][m->cols - 1] != T_WALL)
			error_exit("Map must be surrounded by walls (left/right)");
		r++;
	}
}

static void	fill_tiles_and_count(t_map *m)
{
	size_t	r;
	size_t	c;
	uint8_t	t;

	m->count_p = 0;
	m->count_e = 0;
	m->count_c = 0;
	r = 0;
	while (r < m->rows)
	{
		c = 0;
		while (c < m->cols)
		{
			t = tile_from_char(m->grid[r][c]);
			m->tiles[r][c] = t;
			if (t == T_PLAYER)
			{
				m->count_p++;
				m->px = c;
				m->py = r;
			}
			else if (t == T_EXIT)
				m->count_e++;
			else if (t == T_COL)
				m->count_c++;
			c++;
		}
		r++;
	}
}

static void	check_pec_counts(const t_map *m)
{
	if (m->count_p != 1)
		error_exit("Need exactly 1 player");
	if (m->count_e != 1)
		error_exit("Need exactly 1 exit");
	if (m->count_c < 1)
		error_exit("Need at least 1 collectible");
}

bool	validate_map(t_map *m)
{
	check_rectangular(m);
	alloc_tiles(m);
	fill_tiles_and_count(m);
	check_pec_counts(m);
	check_outer_walls(m);
	return (true);
}
