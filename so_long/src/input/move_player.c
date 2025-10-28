#include "../../include/camera.h"
#include "../../include/game.h"
#include "../../include/map.h"
#include "../../include/render.h"
#include "../../include/utils.h"
#include <stdlib.h>

static void	print_move_count(int moves)
{
	ft_printf("\033[H\033[2J");
	ft_printf("moves: %d\n", moves);
}

static void	apply_move(int nx, int ny)
{
	t_app	*a;

	a = app();
	a->map->px = nx;
	a->map->py = ny;
	a->moves++;
	print_move_count(a->moves);
	redraw();
}

void	move_up(void)
{
	t_app	*a;
	int		nx;
	int		ny;

	a = app();
	nx = a->map->px;
	ny = a->map->py - 1;
	if (ny >= 0 && a->map->tiles[ny][nx] != T_WALL)
		apply_move(nx, ny);
}

void	move_down(void)
{
	t_app	*a;
	int		nx;
	int		ny;

	a = app();
	nx = a->map->px;
	ny = a->map->py + 1;
	if (ny < (int)a->map->rows && a->map->tiles[ny][nx] != T_WALL)
		apply_move(nx, ny);
}

void	move_left(void)
{
	t_app	*a;
	int		nx;
	int		ny;

	a = app();
	nx = a->map->px - 1;
	ny = a->map->py;
	if (nx >= 0 && a->map->tiles[ny][nx] != T_WALL)
		apply_move(nx, ny);
}

void	move_right(void)
{
	t_app *a = app();
	int nx = a->map->px + 1;
	int ny = a->map->py;

	if (nx < (int)a->map->cols && a->map->tiles[ny][nx] != T_WALL)
		apply_move(nx, ny);
}