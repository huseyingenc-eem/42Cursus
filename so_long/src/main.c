/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:05:00 by hgenc             #+#    #+#             */
/*   Updated: 2025/10/31 14:19:42 by hgenc            ###   ########.fr       */
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
    {
        free_map(map);  // ✅ Game başlamadı, lokal temizlik yap
        return (false);
    }
    if (!validate_map_reachable(map))
    {
        free_map(map);  // ✅ Game başlamadı, lokal temizlik yap
        return (false);
    }
    return (true);
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
    t_map map;

    check_args(argc, argv);
    if (!load_and_validate_map(argv[1], &map))
        error_exit("Map validation failed");
    
    // ✅ Buradan sonra ownership app()'e geçer
    if (!game_start(&map))
    {
        // ❌ Burada free_map() ÇAĞIRMA!
        // game_start içinde zaten a->map = map yapılıyor
        // game_cleanup() çağrılmalı
        game_cleanup();
        error_exit("Init fail");
    }
    
    // Normal akış - zaten game_loop sonrası cleanup yok
    // ESC veya X'e basınca game_cleanup() çağrılıyor
    return (0);
}