#include <stdlib.h>
#include <string.h>
#include "../../include/map.h"
#include "../../include/utils.h"

// Sadece oku ve temel parse et
bool load_map(const char *path, t_map *m)
{
    char   *text;
    size_t  rows;

    memset(m, 0, sizeof(*m));
    
    ft_printf("Loading map: %s\n", path);
    
    // Dosyayı oku
    text = read_file(path);
    if (!text)
    {
        ft_printf("Error: Cannot read file %s\n", path);
        return false;
    }
    
    // Satırlara böl
    m->grid = split_lines(text, &rows);
    if (!m->grid || rows == 0)
    {
        ft_printf("Error: Cannot parse file or empty file\n");
        free(text);
        return false;
    }
    
    m->rows = rows;
    m->cols = ft_strlen(m->grid[0]);
    
    if (m->cols == 0)
    {
        ft_printf("Error: Empty first line\n");
        free(text);
        free_map(m);
        return false;
    }
    
    // Çok büyük haritaları reddet
    if (m->rows > 2000 || m->cols > 2000)
    {
        ft_printf("Error: Map too large (%zu x %zu), max 2000x2000\n", 
                 m->rows, m->cols);
        free(text);
        free_map(m);
        return false;
    }
    
    ft_printf("Map loaded: %zu x %zu\n", m->rows, m->cols);
    
    // Grid'i parse ettik, ama henüz validate etmedik
    return true;
}