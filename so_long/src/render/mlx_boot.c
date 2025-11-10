/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_boot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:08:50 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/10 16:54:23 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"
#include "../../include/render.h"
#include "../../mlx/mlx.h"

int	init_window(t_app *a)
{
	int	win_w;
	int	win_h;

	camera_setup_viewport(a->map, &a->camera, VIEW_W, VIEW_H);
	win_w = a->camera.view_w * a->tile_size;
	win_h = a->camera.view_h * a->tile_size;
	a->win = mlx_new_window(a->mlx, win_w, win_h, "so_long");
	if (!a->win)
		return (0);
	return (1);
}
