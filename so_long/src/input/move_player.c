/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:17:03 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/10 16:35:32 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"
#include "../../include/render.h"
#include "../../include/utils.h"
#include <stdlib.h>

static void	check_exit(t_app *a, int nx, int ny)
{
	if (a->map->tiles[ny][nx] == T_EXIT)
	{
		if (a->map->count_c == 0)
		{
			ft_printf("\n🎉 YOU WIN! 🎉\n");
			ft_printf("Total moves: %d\n", a->moves);
			game_cleanup(a);
			exit(0);
		}
		else
			ft_printf("⚠️ Collect all items first! (%d remaining)\n",
				a->map->count_c);
	}
}

static void	apply_move(t_app *a, int nx, int ny)
{
	if (a->map->tiles[ny][nx] == T_COL)
	{
		a->map->tiles[ny][nx] = T_EMPTY;
		a->map->count_c--;
		ft_printf("Collectibles remaining: %d\n", a->map->count_c);
	}
	a->map->px = nx;
	a->map->py = ny;
	a->moves++;
	ft_printf("\033[H\033[2J");
	ft_printf("Moves: %d\n", a->moves);
	redraw(a);
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
	if (a->map->tiles[ny][nx] == T_WALL)
		return ;
	apply_move(a, nx, ny);
}
