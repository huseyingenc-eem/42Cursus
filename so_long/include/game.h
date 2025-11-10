/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 14:28:31 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/10 16:53:09 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "camera.h"
# include "map.h"

typedef struct s_img
{
	void		*ptr;
	int			w;
	int			h;
}				t_img;

typedef struct s_tex
{
	t_img		wall;
	t_img		floor;
	t_img		player;
	t_img		col;
	t_img		exit_tile;
}				t_tex;

typedef struct s_app
{
	void		*mlx;
	void		*win;
	int			moves;
	int			tile_size;
	t_tex		tex;
	t_map		*map;
	t_camera	camera;
}				t_app;

int				game_start(t_app *app_instance);
void			game_cleanup(t_app *app_instance);

#endif
