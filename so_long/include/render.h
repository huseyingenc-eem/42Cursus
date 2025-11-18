/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:02:21 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/14 12:56:19 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# define TILE 64
# define VIEW_W 30
# define VIEW_H 20

struct	s_app;

typedef struct s_cell_pos
{
	int	map_x;
	int	map_y;
	int	scr_x;
	int	scr_y;
}	t_cell_pos;

int		init_window(struct s_app *a);
int		load_textures(struct s_app *a);
void	draw_map(struct s_app *a);

#endif
