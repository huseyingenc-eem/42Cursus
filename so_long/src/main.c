/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:05:00 by hgenc             #+#    #+#             */
/*   Updated: 2025/10/23 16:59:40 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"
#include "../include/game.h"
#include "../include/utils.h"

static bool load_and_validate_map(const char *path, t_map *map)
{
    if (!load_map(path, map))
        return (false);
    return (validate_map(map));
}

static void	check_args(int argc, char **argv)
{
    if (argc != 2)
        error_exit("Error\nUsage: ./so_long <map.ber>");
    if (!has_ber_extension(argv[1]))
        error_exit("Error\nExpected .ber");
}

int	main(int argc, char **argv)
{
    t_map	map;

    check_args(argc, argv);
    if (!load_and_validate_map(argv[1], &map))
        error_exit("Invalid map");
    if (!validate_map_reachable(&map))
    {
        free_map(&map);
        error_exit("No valid path");
    }
    if (!game_start(&map))
    {
        free_map(&map);
        error_exit("Init fail");
    }
    return (0);
}