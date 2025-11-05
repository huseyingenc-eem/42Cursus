/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:02:21 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/05 17:52:05 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# define TILE 64
# define VIEW_W 30
# define VIEW_H 20

struct	s_app;
struct	s_img;

typedef struct s_cell_pos
{
	int	map_x;
	int	map_y;
	int	scr_x;
	int	scr_y;
}	t_cell_pos;

int		init_window(struct s_app *a);
int		load_textures(struct s_app *a);
void	first_draw(struct s_app *a);
void	redraw(struct s_app *a);
void	draw_region(struct s_app *a);
void	draw_hud(struct s_app *a);
void	put_img(struct s_app *a, struct s_img img, int scr_x, int scr_y);

#endif
