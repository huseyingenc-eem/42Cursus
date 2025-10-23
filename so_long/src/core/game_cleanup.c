#include "../../include/game.h"
#include "../../include/map.h"

static void	destroy_images(void)
{
	t_app	*a;

	a = app();
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
}

void	game_cleanup(void)
{
	t_app	*a;

	a = app();
	destroy_images();
	if (a->win)
		mlx_destroy_window(a->mlx, a->win);
	/* bazı mlx sürümlerinde mlx_destroy_display(a->mlx) gerekebilir (Linux) */
	/* free_map() senin map modülünde */
	if (a->map)
		free_map(a->map);
}
