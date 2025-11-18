/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tiles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:00:00 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/14 09:58:44 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map.h"
#include <stdlib.h>

const char	*alloc_tiles(t_map *m)
{
	size_t	r;

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
		return (t_wall);
	if (ch == '0')
		return (t_empty);
	if (ch == 'C')
		return (t_col);
	if (ch == 'E')
		return (t_exit);
	if (ch == 'P')
		return (t_player);
	*err = "Invalid character in map";
	return (t_wall);
}
