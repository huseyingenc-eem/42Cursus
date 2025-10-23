// include/camera.h
#ifndef CAMERA_H
# define CAMERA_H
struct s_map;

typedef struct s_camera
{
	int	start_col;
	int	start_row;
	int	view_w;
	int	view_h;
}	t_camera;

t_camera	*camera(void);
void		camera_setup_viewport(const struct s_map *map,
				int wanted_w, int wanted_h);
void		camera_follow_with_deadzone(const struct s_map *map,
				int margin_x, int margin_y);

#endif
