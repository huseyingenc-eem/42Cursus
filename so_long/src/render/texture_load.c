/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 00:00:00 by you               #+#    #+#             */
/*   Updated: 2025/11/05 16:25:29 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"

static int	load_one(void *mlx_ptr, t_img *out_image, char *file_path)
{
	int	image_w;
	int	image_h;

	out_image->ptr = mlx_xpm_file_to_image(mlx_ptr, file_path,
			&image_w, &image_h);
	out_image->w = image_w;
	out_image->h = image_h;
	if (!out_image->ptr)
		return (0);
	return (1);
}

int	load_textures(t_app *a)
{
	if (!load_one(a->mlx, &a->tex.wall, "assets/textures/wall.xpm"))
		return (0);
	if (!load_one(a->mlx, &a->tex.floor, "assets/textures/floor.xpm"))
		return (0);
	if (!load_one(a->mlx, &a->tex.player, "assets/textures/player.xpm"))
		return (0);
	if (!load_one(a->mlx, &a->tex.col, "assets/textures/collect.xpm"))
		return (0);
	if (!load_one(a->mlx, &a->tex.exit_tile, "assets/textures/exit.xpm"))
		return (0);
	a->tile_size = a->tex.wall.w;
	return (1);
}
