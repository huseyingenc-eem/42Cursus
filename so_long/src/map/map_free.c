#include "../../include/map.h"
#include <stdlib.h>

static void	free_tiles(t_map *m)
{
    size_t	r;

    if (!m->tiles)
        return ;
    r = 0;
    while (r < m->rows)
    {
        if (m->tiles[r])
            free(m->tiles[r]);
        r++;
    }
    free(m->tiles);
    m->tiles = NULL;
}

static void	free_grid(t_map *m)
{
    if (!m->grid)
        return ;
    if (m->grid[0])
        free(m->grid[0]);
    free(m->grid);
    m->grid = NULL;
}

static void	reset_map_values(t_map *m)
{
    m->rows = 0;
    m->cols = 0;
    m->count_p = 0;
    m->count_e = 0;
    m->count_c = 0;
    m->px = 0;
    m->py = 0;
}

void	free_map(t_map *m)
{
    if (!m)
        return ;
    free_tiles(m);
    free_grid(m);
    reset_map_values(m);
}