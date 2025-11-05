/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:25:19 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/05 15:25:27 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"
#include "../../include/input.h"

int	on_key_pressed(int keycode, void *ctx)
{
	t_app	*a;

	a = (t_app *)ctx;
	if (keycode == KEY_ESC)
	{
		game_cleanup(a);
		exit(0);
	}
	else if (keycode == KEY_W)
		move_up(a);
	else if (keycode == KEY_S)
		move_down(a);
	else if (keycode == KEY_A)
		move_left(a);
	else if (keycode == KEY_D)
		move_right(a);
	return (0);
}

int	on_window_close(void *ctx)
{
	t_app *a;

	a = (t_app *)ctx;
	game_cleanup(a);
	exit(0);
	return (0);
}