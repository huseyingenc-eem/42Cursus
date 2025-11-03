/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:06:14 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/03 17:28:40 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"

static void	destroy_textures(t_app *a)
{
	if (!a || !a->mlx)
		return ;
	if (a->tex.wall.ptr)
		mlx_destroy_image(a->mlx, a->tex.wall.ptr);
	if (a->tex.floor.ptr)
		mlx_destroy_image(a->mlx, a->tex.floor.ptr);
	if (a->tex.player.ptr)
		mlx_destroy_image(a->mlx, a->tex.player.ptr);
	if (a->tex.col.ptr)
		mlx_destroy_image(a->mlx, a->tex.col.ptr);
	if (a->tex.exit_tile.ptr)
		mlx_destroy_image(a->mlx, a->tex.exit_tile.ptr);
	a->tex.wall.ptr = NULL;
	a->tex.floor.ptr = NULL;
	a->tex.player.ptr = NULL;
	a->tex.col.ptr = NULL;
	a->tex.exit_tile.ptr = NULL;
}

static void	destroy_window_and_display(t_app *a)
{
	if (!a)
		return ;
	if (a->win && a->mlx)
	{
		mlx_destroy_window(a->mlx, a->win);
		a->win = NULL;
	}
#ifdef __linux__
	if (a->mlx)
	{
		mlx_destroy_display(a->mlx);
		free(a->mlx);
		a->mlx = NULL;
	}
#endif
}

static void	free_map_internal(t_map *m)
{
	size_t	i;

	if (!m)
		return ;
	if (m->tiles)
	{
		i = 0;
		while (i < m->rows)
		{
			if (m->tiles[i])
				free(m->tiles[i]);
			m->tiles[i] = NULL;
			i++;
		}
		free(m->tiles);
		m->tiles = NULL;
	}
	if (m->grid)
	{
		if (m->grid[0])
			free(m->grid[0]);
		free(m->grid);
		m->grid = NULL;
	}
}

void	game_cleanup(void)
{
	t_app	*a;

	a = app();
	if (!a)
		return ;
	destroy_textures(a);
	if (a->map)
	{
		free_map_internal(a->map);
		a->map = NULL;
	}
	destroy_window_and_display(a);
}
