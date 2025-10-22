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
    
    // Dosyayı oku
    text = read_file(path);
    if (!text)
        return false;
    
    // Satırlara böl
    m->grid = split_lines(text, &rows);
    if (!m->grid || rows == 0)
    {
        free(text);
        return false;
    }
    
    m->rows = rows;
    m->cols = ft_strlen(m->grid[0]);
    
    if (m->cols == 0)
    {
        free(text);
        free_map(m);
        return false;
    }
    
    // Grid'i parse ettik, ama henüz validate etmedik
    return true;
}