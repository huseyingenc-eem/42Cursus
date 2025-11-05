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

void		camera_setup_viewport(const struct s_map *map, struct s_camera *cam,
				int wanted_w, int wanted_h);
void		camera_follow(const struct s_map *map, struct s_camera *cam);

#endif
