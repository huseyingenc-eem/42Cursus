/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:05:00 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/05 17:17:40 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"
#include "../include/map.h"
#include "../include/utils.h"

static const char	*load_and_validate_map(const char *path, t_map *map)
{
	const char	*err;

	err = load_map(path, map);
	if (err)
		return (err);
	err = validate_map(map);
	if (err)
		return (err);
	err = validate_map_reachable(map);
	if (err)
		return (err);
	return (NULL);
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
	t_map		map;
	t_app		app_instance;
	size_t		i;
	const char	*err;

	check_args(argc, argv);
	i = 0;
	while (i < sizeof(t_map))
		((char *)&map)[i++] = 0;
	i = 0;
	while (i < sizeof(t_app))
		((char *)&app_instance)[i++] = 0;
	app_instance.map = &map;
	err = load_and_validate_map(argv[1], &map);
	if (err)
	{
		game_cleanup(&app_instance);
		error_exit(err);
	}
	if (!game_start(&app_instance))
	{
		game_cleanup(&app_instance);
		error_exit("Init fail");
	}
	return (0);
}
