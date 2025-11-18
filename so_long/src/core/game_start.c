/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:29:01 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/14 12:52:21 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"
#include "../../include/input.h"
#include "../../include/render.h"
#include "../../mlx/mlx.h"

static void	install_hooks(t_app *a)
{
	mlx_key_hook(a->win, &on_key_pressed, a);
	mlx_hook(a->win, 17, 0, &on_window_close, a);
}

int	game_start(t_app *a)
{
	a->tile_size = 0;
	a->mlx = mlx_init();
	if (!a->mlx)
		return (0);
	if (!load_textures(a))
		return (0);
	if (!init_window(a))
		return (0);
	camera_follow(a->map, &a->camera);
	draw_map(a);
	install_hooks(a);
	mlx_loop(a->mlx);
	return (1);
}
