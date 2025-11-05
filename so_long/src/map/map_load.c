/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:45:55 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/05 16:25:29 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map.h"
#include "../../include/utils.h"
#include <stdlib.h>

const char	*load_map(const char *path, t_map *m)
{
	char	*text;
	size_t	rows;
	size_t	i;

	i = 0;
	while (i < sizeof(*m))
		((char *)m)[i++] = 0;
	text = read_file(path);
	if (!text)
		return ("Cannot read map file");
	m->grid = split_lines(text, &rows);
	if (!m->grid || rows == 0)
		return ("Empty or unparsable map file");
	m->rows = rows;
	m->cols = ft_strlen(m->grid[0]);
	if (m->cols == 0)
		return ("Empty first line");
	if (m->rows > 2000 || m->cols > 2000)
		return ("Map too large (max 2000x2000)");
	return (NULL);
}
