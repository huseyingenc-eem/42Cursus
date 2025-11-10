/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:59:04 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/10 16:31:11 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"
#include "../../include/render.h"

void	first_draw(t_app *a)
{
	camera_follow(a->map, &a->camera);
	draw_region(a);
	draw_hud(a);
}

void	redraw(t_app *a)
{
	camera_follow(a->map, &a->camera);
	draw_region(a);
	draw_hud(a);
}
