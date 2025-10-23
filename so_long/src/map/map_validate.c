#include "../../include/map.h"
#include "../../include/utils.h"
#include <stdlib.h>
#include <string.h>

// Karakter → Tile enum'a çevir
static uint8_t tile_from_char(char ch)
{
    if (ch == '1') return T_WALL;
    if (ch == '0') return T_EMPTY;
    if (ch == 'C') return T_COL;
    if (ch == 'E') return T_EXIT;
    if (ch == 'P') return T_PLAYER;
    return T_WALL; // Default duvar yap
}

// Tiles dizisi için memory ayır - GÜVENLE
static bool alloc_tiles(t_map *m)
{
    size_t r;
    
    // Çok büyük haritaları reddet
    if (m->rows > 2000 || m->cols > 2000)
    {
        ft_printf("Error: Map too large (%zu x %zu)\n", m->rows, m->cols);
        return false;
    }
    
    m->tiles = malloc(sizeof(uint8_t *) * m->rows);
    if (!m->tiles)
        return false;
    
    // Başlangıçta NULL'la
    for (r = 0; r < m->rows; r++)
        m->tiles[r] = NULL;
    
    // Her satır için memory ayır
    for (r = 0; r < m->rows; r++)
    {
        m->tiles[r] = malloc(sizeof(uint8_t) * m->cols);
        if (!m->tiles[r])
        {
            // Hata durumunda önceki satırları temizle
            for (size_t i = 0; i < r; i++)
            {
                free(m->tiles[i]);
                m->tiles[i] = NULL;
            }
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
    size_t r;
    
    for (r = 0; r < m->rows; r++)
    {
        if (ft_strlen(m->grid[r]) != m->cols)
        {
            ft_printf("Error: Row %zu length mismatch\n", r);
            return false;
        }
    }
    return true;
}

// Dış duvarlar tamamen '1' mi?
static bool check_outer_walls(const t_map *m)
{
    size_t c, r;
    
    // Üst ve alt satır
    for (c = 0; c < m->cols; c++)
    {
        if (m->tiles[0][c] != T_WALL || m->tiles[m->rows - 1][c] != T_WALL)
            return false;
    }
    
    // Sol ve sağ sütun
    for (r = 0; r < m->rows; r++)
    {
        if (m->tiles[r][0] != T_WALL || m->tiles[r][m->cols - 1] != T_WALL)
            return false;
    }
    return true;
}

// Geçerli karakterler mi + P/E/C sayılarını say + tiles dizisini doldur
static bool fill_tiles_and_count(t_map *m)
{
    size_t r, c;
    uint8_t tile;
    
    m->count_p = 0;
    m->count_e = 0;
    m->count_c = 0;
    
    for (r = 0; r < m->rows; r++)
    {
        for (c = 0; c < m->cols; c++)
        {
            tile = tile_from_char(m->grid[r][c]);
            
            // Geçersiz karakter kontrolü
            if (tile == T_WALL && m->grid[r][c] != '1')
            {
                ft_printf("Error: Invalid char '%c' at (%zu,%zu)\n", 
                         m->grid[r][c], r, c);
                return false;
            }
            
            m->tiles[r][c] = tile;
            
            if (tile == T_PLAYER)
            {
                m->count_p++;
                m->px = c;
                m->py = r;
            }
            else if (tile == T_EXIT)
                m->count_e++;
            else if (tile == T_COL)
                m->count_c++;
        }
    }
    return true;
}

// P/E/C sayıları doğru mu?
static bool check_pec_counts(const t_map *m)
{
    if (m->count_p != 1)
    {
        ft_printf("Error: Need exactly 1 player, found %d\n", m->count_p);
        return false;
    }
    if (m->count_e != 1)
    {
        ft_printf("Error: Need exactly 1 exit, found %d\n", m->count_e);
        return false;
    }
    if (m->count_c < 1)
    {
        ft_printf("Error: Need at least 1 collectible, found %d\n", m->count_c);
        return false;
    }
    return true;
}

// ANA VALIDATION FONKSİYONU
bool validate_map(t_map *m)
{
    ft_printf("Validating map: %zu x %zu\n", m->rows, m->cols);
    
    if (!check_rectangular(m))
        return false;
        
    if (!alloc_tiles(m))
    {
        ft_printf("Error: Memory allocation failed\n");
        return false;
    }
    
    if (!fill_tiles_and_count(m))
        return false;
        
    if (!check_pec_counts(m))
        return false;
        
    if (!check_outer_walls(m))
    {
        ft_printf("Error: Map not surrounded by walls\n");
        return false;
    }
    
    ft_printf("Map validation successful\n");
    return true;
}