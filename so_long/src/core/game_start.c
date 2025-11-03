/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:29:01 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/03 17:29:06 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"
#include "../../include/render.h"
#include "../../include/input.h"
#include "../../include/camera.h"
#include "../../include/map.h"
#include "../../include/utils.h"

static void	install_hooks(void)
{
	t_app	*a;

	a = app();
	mlx_key_hook(a->win, &on_key_pressed, NULL);
	mlx_hook(a->win, 17, 0, &on_window_close, NULL);
}

int	game_start(t_map *map)
{
	t_app *a = app();
	
	a->map = map;
	a->tile_size = 0;
	
	a->mlx = mlx_init();
	if (!a->mlx)
		return (0);
		
	if (!load_textures())
		return (0);
		
	if (!init_window())
		return (0);
		
	camera_follow(map);
	first_draw();
	install_hooks();
	mlx_loop(a->mlx);
	return (1);
}
