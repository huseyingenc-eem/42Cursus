/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 00:00:00 by you               #+#    #+#             */
/*   Updated: 2025/10/31 15:21:02 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"
#include "../../include/render.h"
#include "../../include/camera.h"
#include "../../include/map.h"

static void	put_img(t_img img, int scr_x, int scr_y)
{
	t_app	*a;

	a = app();
	mlx_put_image_to_window(a->mlx, a->win, img.ptr, scr_x * a->tile_size, scr_y * a->tile_size);
}

static void	draw_cell(int map_x, int map_y, int scr_x, int scr_y)
{
	t_app	*a;

	a = app();
	put_img(a->tex.floor, scr_x, scr_y);
	if (a->map->tiles[map_y][map_x] == 0)
		put_img(a->tex.wall, scr_x, scr_y);
	else if (a->map->tiles[map_y][map_x] == 2)
		put_img(a->tex.col, scr_x, scr_y);
	else if (a->map->tiles[map_y][map_x] == 3)
		put_img(a->tex.exit_tile, scr_x, scr_y);
}

static void	draw_region(void)
{
	t_camera	*cam;
	t_app		*a;
	int			screen_y;
	int			screen_x;
	int			map_y;
	int			map_x;

	a = app();
	cam = camera();
	screen_y = 0;
	while (screen_y < cam->view_h)
	{
		screen_x = 0;
		while (screen_x < cam->view_w)
		{
			map_y = cam->start_row + screen_y;
			map_x = cam->start_col + screen_x;
			draw_cell(map_x, map_y, screen_x, screen_y);
			screen_x++;
		}
		screen_y++;
	}
	if (a->map->px >= cam->start_col && a->map->px < cam->start_col + cam->view_w
		&& a->map->py >= cam->start_row && a->map->py < cam->start_row + cam->view_h)
		put_img(a->tex.player,
			a->map->px - cam->start_col, a->map->py - cam->start_row);
}

void	first_draw(void)
{
	camera_follow_with_deadzone(app()->map, 10, 8);
	draw_region();
}

void	redraw(void)
{
	camera_follow_with_deadzone(app()->map, 10, 8);
	draw_region();
}
