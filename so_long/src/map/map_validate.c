/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:20:00 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/10 16:42:40 by hgenc            ###   ########.fr       */
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

static void	count_tile(t_map *m, int tile, size_t r, size_t c)
{
	if (tile == T_PLAYER)
	{
		m->count_p++;
		m->px = c;
		m->py = r;
	}
	else if (tile == T_EXIT)
		m->count_e++;
	else if (tile == T_COL)
		m->count_c++;
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
			count_tile(m, t, r, c);
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
