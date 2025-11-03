/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:45:55 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/03 17:46:33 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map.h"
#include "../../include/utils.h"

bool	load_map(const char *path, t_map *m)
{
	char	*text;
	size_t	rows;

	ft_memset(m, 0, sizeof(*m));
	ft_printf("Loading map: %s\n", path);
	text = read_file(path);
	if (!text)
		error_exit("Cannot read map file");
	m->grid = split_lines(text, &rows);
	if (!m->grid || rows == 0)
		error_exit("Empty or unparsable map file");
	m->rows = rows;
	m->cols = ft_strlen(m->grid[0]);
	if (m->cols == 0)
		error_exit("Empty first line");
	if (m->rows > 2000 || m->cols > 2000)
		error_exit("Map too large (max 2000x2000)");
	return (true);
}
