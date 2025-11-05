/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:59:04 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/05 16:25:29 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/camera.h"
#include "../../include/game.h"
#include "../../include/map.h"

static void	put_img(t_app *a, t_img img, int scr_x, int scr_y)
{
	mlx_put_image_to_window(a->mlx, a->win, img.ptr,
		scr_x * a->tile_size, scr_y * a->tile_size);
}

static void	draw_cell(t_app *a, int map_x, int map_y, int scr_x, int scr_y)
{
	put_img(a, a->tex.floor, scr_x, scr_y);
	if (a->map->tiles[map_y][map_x] == T_WALL)
		put_img(a, a->tex.wall, scr_x, scr_y);
	else if (a->map->tiles[map_y][map_x] == T_COL)
		put_img(a, a->tex.col, scr_x, scr_y);
	else if (a->map->tiles[map_y][map_x] == T_EXIT)
		put_img(a, a->tex.exit_tile, scr_x, scr_y);
}

static void	draw_region(t_app *a)
{
	t_camera	*cam;
	int			sy;
	int			sx;

	cam = &(a->camera);
	sy = 0;
	while (sy < cam->view_h)
	{
		sx = 0;
		while (sx < cam->view_w)
		{
			draw_cell(a, cam->start_col + sx, cam->start_row + sy, sx, sy);
			sx++;
		}
		sy++;
	}
	if (a->map->px >= cam->start_col && a->map->px < cam->start_col + cam->view_w
		&& a->map->py >= cam->start_row && a->map->py < cam->start_row + cam->view_h)
		put_img(a, a->tex.player,
			a->map->px - cam->start_col, a->map->py - cam->start_row);
}

void	first_draw(t_app *a)
{
	camera_follow(a->map, &a->camera);
	draw_region(a);
}

void	redraw(t_app *a)
{
	camera_follow(a->map, &a->camera);
	draw_region(a);
}
