/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:23:19 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/10 16:54:38 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"
#include "../../mlx/mlx.h"

static void	num_to_str(int num, char *str)
{
	int		i;
	int		temp;

	if (num == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return ;
	}
	i = 0;
	temp = num;
	while (temp > 0)
	{
		temp /= 10;
		i++;
	}
	str[i] = '\0';
	while (i > 0)
	{
		i--;
		str[i] = (num % 10) + '0';
		num /= 10;
	}
}

void	draw_hud(t_app *a)
{
	char	moves_str[12];
	char	text[32];
	int		i;
	int		j;

	num_to_str(a->moves, moves_str);
	i = 0;
	while ("Moves: "[i])
	{
		text[i] = "Moves: "[i];
		i++;
	}
	j = 0;
	while (moves_str[j])
	{
		text[i] = moves_str[j];
		i++;
		j++;
	}
	text[i] = '\0';
	mlx_string_put(a->mlx, a->win, 10, 20, 0xFFFFFF, text);
}
