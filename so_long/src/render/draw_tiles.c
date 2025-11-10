/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tiles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:59:04 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/10 16:54:30 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"
#include "../../include/render.h"
#include "../../mlx/mlx.h"

void	put_img(t_app *a, t_img img, int scr_x, int scr_y)
{
	mlx_put_image_to_window(a->mlx, a->win, img.ptr,
		scr_x * a->tile_size, scr_y * a->tile_size);
}

static void	draw_cell(t_app *a, t_cell_pos pos)
{
	put_img(a, a->tex.floor, pos.scr_x, pos.scr_y);
	if (a->map->tiles[pos.map_y][pos.map_x] == T_WALL)
		put_img(a, a->tex.wall, pos.scr_x, pos.scr_y);
	else if (a->map->tiles[pos.map_y][pos.map_x] == T_COL)
		put_img(a, a->tex.col, pos.scr_x, pos.scr_y);
	else if (a->map->tiles[pos.map_y][pos.map_x] == T_EXIT)
		put_img(a, a->tex.exit_tile, pos.scr_x, pos.scr_y);
}

static int	player_visible(t_app *a, t_camera *cam)
{
	if (a->map->px >= cam->start_col
		&& a->map->px < cam->start_col + cam->view_w
		&& a->map->py >= cam->start_row
		&& a->map->py < cam->start_row + cam->view_h)
		return (1);
	return (0);
}

void	draw_region(t_app *a)
{
	t_camera	*cam;
	t_cell_pos	pos;
	int			sy;
	int			sx;

	cam = &(a->camera);
	sy = 0;
	while (sy < cam->view_h)
	{
		sx = 0;
		while (sx < cam->view_w)
		{
			pos.map_x = cam->start_col + sx;
			pos.map_y = cam->start_row + sy;
			pos.scr_x = sx;
			pos.scr_y = sy;
			draw_cell(a, pos);
			sx++;
		}
		sy++;
	}
	if (player_visible(a, cam))
		put_img(a, a->tex.player,
			a->map->px - cam->start_col, a->map->py - cam->start_row);
}
