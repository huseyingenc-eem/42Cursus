#include "../../include/map.h"
#include <stdlib.h>

void free_map(t_map *m)
{
    if (!m)
        return;
    
    // tiles dizisini temizle
    if (m->tiles)
    {
        for (size_t r = 0; r < m->rows; r++)
            free(m->tiles[r]);
        free(m->tiles);
        m->tiles = NULL;
    }
    
    // grid'i temizle (split_lines'dan gelen pointer array)
    if (m->grid)
    {
        free(m->grid[0]); // İlk satır = orjinal text'in başlangıcı
        free(m->grid);    // Pointer array'i
        m->grid = NULL;
    }
}