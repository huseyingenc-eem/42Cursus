#include "../../include/camera.h"
#include "../../include/map.h"

static t_camera	g_cam;

t_camera	*camera(void)
{
	return (&g_cam);
}

void	camera_setup_viewport(const t_map *map, int wanted_w, int wanted_h)
{
	t_camera	*cam;

	cam = camera();
	if ((int)map->cols <= wanted_w)
		cam->view_w = map->cols;
	else
		cam->view_w = wanted_w;
	if ((int)map->rows <= wanted_h)
		cam->view_h = map->rows;
	else
		cam->view_h = wanted_h;
}

void	camera_follow_with_deadzone(const t_map *map, int margin_x,
		int margin_y)
{
	t_camera	*cam;
	int			target_col;
	int			target_row;

	cam = camera();
	target_col = map->px - cam->view_w / 2;
	target_row = map->py - cam->view_h / 2;
	if (target_col < 0)
		target_col = 0;
	if (target_row < 0)
		target_row = 0;
	if (target_col + cam->view_w > (int)map->cols)
		target_col = map->cols - cam->view_w;
	if (target_row + cam->view_h > (int)map->rows)
		target_row = map->rows - cam->view_h;
	cam->start_col = target_col;
	cam->start_row = target_row;
	(void)margin_x;
	(void)margin_y;
}
