/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_walls.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:12:05 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/05 17:33:57 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map.h"

const char	*check_outer_walls(const t_map *m)
{
	size_t	c;
	size_t	r;

	c = -1;
	while (++c < m->cols)
		if (m->tiles[0][c] != T_WALL
			|| m->tiles[m->rows - 1][c] != T_WALL)
			return ("Map must be surrounded by walls (top/bottom)");
	r = -1;
	while (++r < m->rows)
		if (m->tiles[r][0] != T_WALL
			|| m->tiles[r][m->cols - 1] != T_WALL)
			return ("Map must be surrounded by walls (left/right)");
	return (NULL);
}
