/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:28:49 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/05 15:15:28 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"
#include "../../include/input.h"

void	install_hooks(void)
{
	t_app	*a;

	a = app();
	mlx_key_hook(a->win, &on_key_pressed, 0);
	mlx_hook(a->win, 17, 0, &on_window_close, 0);
}

int	on_key_pressed(int keycode, void *ctx)
{
	(void)ctx;
	if (keycode == KEY_ESC)
	{
		game_cleanup();
		exit(0);
	}
	else if (keycode == KEY_W)
		move_up();
	else if (keycode == KEY_S)
		move_down();
	else if (keycode == KEY_A)
		move_left();
	else if (keycode == KEY_D)
		move_right();
	return (0);
}

int	on_window_close(void *ctx)
{
	(void)ctx;
	game_cleanup();
	exit(0);
	return (0);
}
