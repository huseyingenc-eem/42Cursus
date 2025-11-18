/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:45:55 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/14 09:50:39 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map.h"
#include "../../include/utils.h"

const char	*load_map(const char *path, t_map *m)
{
	char	*text;

	text = read_file(path);
	if (!text)
		return ("Cannot read map file");
	m->grid = split_lines(text, &m->rows);
	if (!m->grid || m->rows == 0)
		return ("Empty or unparsable map file");
	m->cols = ft_strlen(m->grid[0]);
	if (m->cols == 0)
		return ("Empty first line");
	if (m->rows > MAX_DIM || m->cols > MAX_DIM)
		return ("Map too large (max 2000x2000)");
	return (NULL);
}
