/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:58:11 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/05 17:56:30 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

struct	s_app;

int		on_key_pressed(int keycode, void *ctx);
int		on_window_close(void *ctx);

void	try_move(struct s_app *a, int dx, int dy);

#endif
