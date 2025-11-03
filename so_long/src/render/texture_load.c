/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 00:00:00 by you               #+#    #+#             */
/*   Updated: 2025/11/03 14:46:29 by hgenc            ###   ########.fr       */
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

bool	load_textures(void)
{
	t_app	*app_ctx;

	app_ctx = app();
	if (!load_one(app_ctx->mlx, &app_ctx->tex.wall, "assets/textures/wall.xpm"))
		return (false);
	if (!load_one(app_ctx->mlx, &app_ctx->tex.floor, "assets/textures/floor.xpm"))
		return (false);
	if (!load_one(app_ctx->mlx, &app_ctx->tex.player, "assets/textures/player.xpm"))
		return (false);
	if (!load_one(app_ctx->mlx, &app_ctx->tex.col, "assets/textures/collect.xpm"))
		return (false);
	if (!load_one(app_ctx->mlx, &app_ctx->tex.exit_tile, "assets/textures/exit.xpm"))
		return (false);
	
	app_ctx->tile_size = app_ctx->tex.wall.w;
	
	return (true);
}
