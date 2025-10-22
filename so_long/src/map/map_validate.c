#include "../../include/map.h"
#include "../../include/utils.h"
#include <stdlib.h>

// Karakter → Tile enum'a çevir
static uint8_t tile_from_char(char ch)
{
    if (ch == '1') return T_WALL;
    if (ch == '0') return T_EMPTY;
    if (ch == 'C') return T_COL;
    if (ch == 'E') return T_EXIT;
    if (ch == 'P') return T_PLAYER;
    return 255; // Geçersiz karakter
}

// Tiles dizisi için memory ayır
static bool alloc_tiles(t_map *m)
{
    m->tiles = malloc(sizeof(uint8_t *) * m->rows);
    if (!m->tiles)
        return false;
    
    for (size_t r = 0; r < m->rows; r++)
    {
        m->tiles[r] = malloc(sizeof(uint8_t) * m->cols);
        if (!m->tiles[r])
        {
            // Önceki satırları temizle
            for (size_t i = 0; i < r; i++)
                free(m->tiles[i]);
            free(m->tiles);
            m->tiles = NULL;
            return false;
        }
    }
    return true;
}

// Dikdörtgen mi kontrol et
static bool check_rectangular(const t_map *m)
{
    for (size_t r = 0; r < m->rows; r++)
    {
        if (ft_strlen(m->grid[r]) != m->cols)
            return false;
    }
    return true;
}

// Dış duvarlar tamamen '1' mi?
static bool check_outer_walls(const t_map *m)
{
    // Üst ve alt satır
    for (size_t c = 0; c < m->cols; c++)
    {
        if (m->grid[0][c] != '1')
            return false;
        if (m->grid[m->rows - 1][c] != '1')
            return false;
    }
    
    // Sol ve sağ sütun
    for (size_t r = 0; r < m->rows; r++)
    {
        if (m->grid[r][0] != '1')
            return false;
        if (m->grid[r][m->cols - 1] != '1')
            return false;
    }
    
    return true;
}

// Geçerli karakterler mi + P/E/C sayılarını say + tiles dizisini doldur
static bool fill_tiles_and_count(t_map *m)
{
    m->count_p = 0;
    m->count_e = 0;
    m->count_c = 0;
    
    for (size_t r = 0; r < m->rows; r++)
    {
        for (size_t c = 0; c < m->cols; c++)
        {
            char ch = m->grid[r][c];
            uint8_t tile = tile_from_char(ch);
            
            // Geçersiz karakter?
            if (tile == 255)
                return false;
            
            m->tiles[r][c] = tile;
            
            // P/E/C say
            if (ch == 'P')
            {
                m->count_p++;
                m->py = r;
                m->px = c;
            }
            else if (ch == 'E')
                m->count_e++;
            else if (ch == 'C')
                m->count_c++;
        }
    }
    
    return true;
}

// P/E/C sayıları doğru mu?
static bool check_pec_counts(const t_map *m)
{
    if (m->count_p != 1)
        return false; // Tam 1 tane P olmalı
    if (m->count_e != 1)
        return false; // Tam 1 tane E olmalı
    if (m->count_c < 1)
        return false; // En az 1 tane C olmalı
    return true;
}

// ANA VALIDATION FONKSİYONU
bool validate_map(t_map *m)
{
    // 1. Dikdörtgen mi?
    if (!check_rectangular(m))
    {
        error_exit("Map must be rectangular");
        return false;
    }
    
    // 2. Dış duvarlar tamam mı?
    if (!check_outer_walls(m))
    {
        error_exit("Map must be surrounded by walls");
        return false;
    }
    
    // 3. Tiles dizisini ayır
    if (!alloc_tiles(m))
    {
        error_exit("Memory allocation failed");
        return false;
    }
    
    // 4. Tiles'ı doldur + geçerli karakterler + P/E/C say
    if (!fill_tiles_and_count(m))
    {
        error_exit("Invalid character in map (only 0,1,C,E,P allowed)");
        return false;
    }
    
    // 5. P/E/C sayıları doğru mu?
    if (!check_pec_counts(m))
    {
        error_exit("Map must have exactly 1 Player, 1 Exit, and at least 1 Collectible");
        return false;
    }
    
    return true;
}