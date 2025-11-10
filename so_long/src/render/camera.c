/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 00:00:00 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/10 16:31:11 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/camera.h"
#include "../../include/map.h"

void	camera_setup_viewport(const t_map *map, t_camera *cam, int wanted_w,
		int wanted_h)
{
	if ((int)map->cols <= wanted_w)
		cam->view_w = map->cols;
	else
		cam->view_w = wanted_w;
	if ((int)map->rows <= wanted_h)
		cam->view_h = map->rows;
	else
		cam->view_h = wanted_h;
}

void	camera_follow(const t_map *map, t_camera *cam)
{
	int	target_col;
	int	target_row;

	target_col = map->px - cam->view_w / 2;
	target_row = map->py - cam->view_h / 2;
	if (target_col < 0)
		target_col = 0;
	if (target_row < 0)
		target_row = 0;
	if (target_col + cam->view_w > (int)map->cols)
		target_col = map->cols - cam->view_w;
	if (target_row + cam->view_h > (int)map->rows)
		target_row = map->rows - cam->view_h;
	cam->start_col = target_col;
	cam->start_row = target_row;
}
