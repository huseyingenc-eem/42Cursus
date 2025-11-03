/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:59:04 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/03 17:23:44 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/game.h"
#include "../../include/camera.h"

static void	ft_put_image(t_img img, int screen_tile_x, int screen_tile_y)
{
	t_app	*app_instance;

	app_instance = app();
	mlx_put_image_to_window(app_instance->mlx, app_instance->win, img.ptr,
		screen_tile_x * app_instance->tile_size,
		screen_tile_y * app_instance->tile_size);
}

static void	ft_draw_cell(int map_x, int map_y, int screen_tile_x, int screen_tile_y)
{
	t_app	*app_instance;

	app_instance = app();
	ft_put_image(app_instance->tex.floor, screen_tile_x, screen_tile_y);
	if (app_instance->map->tiles[map_y][map_x] == 0)
		ft_put_image(app_instance->tex.wall, screen_tile_x, screen_tile_y);
	else if (app_instance->map->tiles[map_y][map_x] == 2)
		ft_put_image(app_instance->tex.col, screen_tile_x, screen_tile_y);
	else if (app_instance->map->tiles[map_y][map_x] == 3)
		ft_put_image(app_instance->tex.exit_tile, screen_tile_x, screen_tile_y);
}

static void	ft_draw_region(void)
{
	t_camera	*cam;
	t_app		*a;
	int			screen_y;
	int			screen_x;
	int			map_y;
	int			map_x;

	a = app();
	cam = &(app()->camera);
	screen_y = -1;
	while (++screen_y < cam->view_h)
	{
		screen_x = -1;
		while (++screen_x < cam->view_w)
		{
			map_y = cam->start_row + screen_y;
			map_x = cam->start_col + screen_x;
			ft_draw_cell(map_x, map_y, screen_x, screen_y);
		}
	}
	if (a->map->px >= cam->start_col && a->map->px < cam->start_col + cam->view_w
		&& a->map->py >= cam->start_row && a->map->py < cam->start_row + cam->view_h)
		ft_put_image(a->tex.player,
			a->map->px - cam->start_col, a->map->py - cam->start_row);
}

void	first_draw(void)
{
	camera_follow(app()->map);
	ft_draw_region();
}

void	redraw(void)
{
	camera_follow(app()->map);
	ft_draw_region();
}
