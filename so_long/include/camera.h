/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:02:06 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/14 12:49:49 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "map.h"

typedef struct s_camera
{
	int	start_col;
	int	start_row;
	int	view_w;
	int	view_h;
}		t_camera;

void	camera_setup_viewport(const struct s_map *map, struct s_camera *cam,
			int wanted_w, int wanted_h);
void	camera_follow(const struct s_map *map, struct s_camera *cam);

#endif
