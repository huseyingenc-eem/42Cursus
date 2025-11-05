#include "../../include/camera.h"
#include "../../include/game.h"
#include "../../include/render.h"

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
