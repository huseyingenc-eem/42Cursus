/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:25:19 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/05 18:01:40 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"
#include "../../include/input.h"
#include <stdlib.h>

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
		try_move(a, 0, -1);
	else if (keycode == KEY_S)
		try_move(a, 0, 1);
	else if (keycode == KEY_A)
		try_move(a, -1, 0);
	else if (keycode == KEY_D)
		try_move(a, 1, 0);
	return (0);
}

int	on_window_close(void *ctx)
{
	t_app	*a;

	a = (t_app *)ctx;
	game_cleanup(a);
	exit(0);
	return (0);
}
