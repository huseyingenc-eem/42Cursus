/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tiles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:00:00 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/05 16:59:17 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map.h"
#include <stdlib.h>

const char	*alloc_tiles(t_map *m)
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

int	tile_from_char(char ch, const char **err)
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
