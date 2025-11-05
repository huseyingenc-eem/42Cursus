/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:20:00 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/05 16:25:29 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map.h"
#include "../../include/utils.h"
#include <stdlib.h>

static int	tile_from_char(char ch, const char **err)
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
	*err = "Invalid character in map";
	return (T_WALL);
}

static const char	*alloc_tiles(t_map *m)
{
	size_t	r;

	if (m->rows > 2000 || m->cols > 2000)
		return ("Map too large");
	m->tiles = (int **)malloc(sizeof(int *) * m->rows);
	if (!m->tiles)
		return ("Allocation failed (tiles)");
	r = -1;
	while (++r < m->rows)
		m->tiles[r] = NULL;
	r = -1;
	while (++r < m->rows)
	{
		m->tiles[r] = (int *)malloc(sizeof(int) * m->cols);
		if (!m->tiles[r])
			return ("Allocation failed (tiles row)");
	}
	return (NULL);
}

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

static const char	*check_outer_walls(const t_map *m)
{
	size_t	c;
	size_t	r;

	c = 0;
	while (c < m->cols)
	{
		if (m->tiles[0][c] != T_WALL
			|| m->tiles[m->rows - 1][c] != T_WALL)
			return ("Map must be surrounded by walls (top/bottom)");
		c++;
	}
	r = 0;
	while (r < m->rows)
	{
		if (m->tiles[r][0] != T_WALL
			|| m->tiles[r][m->cols - 1] != T_WALL)
			return ("Map must be surrounded by walls (left/right)");
		r++;
	}
	return (NULL);
}

static const char	*fill_tiles_and_count(t_map *m)
{
	size_t		r;
	size_t		c;
	int			t;
	const char	*err;

	m->count_p = 0;
	m->count_e = 0;
	m->count_c = 0;
	r = -1;
	while (++r < m->rows)
	{
		c = -1;
		while (++c < m->cols)
		{
			err = NULL;
			t = tile_from_char(m->grid[r][c], &err);
			if (err)
				return (err);
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
