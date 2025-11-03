/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:05:00 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/03 17:58:08 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"
#include "../include/map.h"
#include "../include/utils.h"

static bool	load_and_validate_map(const char *path, t_map *map)
{
	if (!load_map(path, map))
		return (false);
	if (!validate_map(map))
		return (false);
	if (!validate_map_reachable(map))
		return (false);
	return (true);
}

static void	check_args(int argc, char **argv)
{
	if (argc != 2)
		error_exit("Usage: ./so_long <map.ber>");
	if (!has_ber_extension(argv[1]))
		error_exit("Expected <mapname>.ber");
}

int	main(int argc, char **argv)
{
	t_map map;

	check_args(argc, argv);
	if (!load_and_validate_map(argv[1], &map))
		error_exit("Map validation failed");

	if (!game_start(&map))
	{
		game_cleanup();
		error_exit("Init fail");
	}
	return (0);
}