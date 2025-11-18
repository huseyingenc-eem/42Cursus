/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:17:03 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/14 12:54:43 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"
#include "../../include/render.h"
#include "../../include/utils.h"
#include <stdlib.h>

static void	check_exit(t_app *a, int nx, int ny)
{
	if (a->map->tiles[ny][nx] == t_exit)
	{
		if (a->map->count_c == 0)
		{
			ft_printf("YOU WIN!\n");
			game_cleanup(a);
			exit(0);
		}
	}
}

static void	apply_move(t_app *a, int nx, int ny)
{
	if (a->map->tiles[ny][nx] == t_col)
	{
		a->map->tiles[ny][nx] = t_empty;
		a->map->count_c--;
	}
	a->map->px = nx;
	a->map->py = ny;
	a->moves++;
	ft_printf("\033[H\033[2J");
	ft_printf("Moves: %d\n", a->moves);
	draw_map(a);
	check_exit(a, nx, ny);
}

void	try_move(t_app *a, int dx, int dy)
{
	int	nx;
	int	ny;

	nx = a->map->px + dx;
	ny = a->map->py + dy;
	if (nx < 0 || ny < 0)
		return ;
	if (nx >= (int)a->map->cols || ny >= (int)a->map->rows)
		return ;
	if (a->map->tiles[ny][nx] == t_wall)
		return ;
	apply_move(a, nx, ny);
}
