#include "../include/utils.h"
#include "../include/map.h"

static void	print_stats(const t_map *map)
{
    ft_printf("rows: %d\n", (int)map->rows);
    ft_printf("cols: %d\n", (int)map->cols);
    ft_printf("P: %d  E: %d  C: %d\n", map->count_p, map->count_e, map->count_c);
    ft_printf("P at (y,x): %d, %d\n", map->py, map->px);
}

static void	print_grid(const t_map *map)
{
    size_t	row;

    ft_printf("== Original grid ==\n");
    row = 0;
    while (row < map->rows)
    {
        ft_printf("%s\n", map->grid[row]);
        row++;
    }
}

static void	print_tiles(const t_map *map)
{
    size_t	row;
    size_t	col;

    ft_printf("== Tiles (numeric) ==\n");
    row = 0;
    while (row < map->rows)
    {
        col = 0;
        while (col < map->cols)
        {
            ft_printf("%d", map->tiles[row][col]);
            col++;
        }
        ft_printf("\n");
        row++;
    }
}

int	main(int argc, char **argv)
{
    t_map	map;

    if (argc != 2)
    {
        error_exit("Usage: ./so_long <map.ber>");
        return (1);
    }
    ft_printf("[STEP 0] Checking file extension...\n");
    if (!has_ber_extension(argv[1]))
    {
        error_exit("Map file must have .ber extension");
        return (1);
    }
    ft_printf("[STEP 1] Loading map file...\n");
    if (!load_map(argv[1], &map))
    {
        error_exit("Failed to load map file");
        return (1);
    }
    ft_printf("[STEP 2] Validating map structure...\n");
    if (!validate_map(&map))
    {
        free_map(&map);
        return (1);
    }
    print_stats(&map);
    print_grid(&map);
    print_tiles(&map);
    ft_printf("[STEP 3] Checking reachability (BFS)...\n");
    if (!validate_map_reachable(&map))
    {
        error_exit("Map is not solvable");
        free_map(&map);
        return (1);
    }
    ft_printf("[OK] Map is valid and solvable!\n");
    free_map(&map);
    return (0);
}