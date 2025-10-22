#include "../../include/map.h"
#include <stdlib.h>
#include <string.h>

typedef struct s_point {
    int y;
    int x;
} t_point;

static bool **alloc_visited(size_t rows, size_t cols)
{
    bool **vis = malloc(sizeof(bool *) * rows);
    if (!vis) return NULL;
    
    for (size_t r = 0; r < rows; r++)
    {
        vis[r] = malloc(sizeof(bool) * cols);
        if (!vis[r])
        {
            // Önceki satırları temizle
            for (size_t i = 0; i < r; i++)
                free(vis[i]);
            free(vis);
            return NULL;
        }
        memset(vis[r], 0, sizeof(bool) * cols);
    }
    return vis;
}

static void free_visited(bool **vis, size_t rows)
{
    if (!vis) return;
    for (size_t r = 0; r < rows; r++)
        free(vis[r]);
    free(vis);
}

bool validate_map_reachable(const t_map *m)
{
    bool **vis = alloc_visited(m->rows, m->cols);
    if (!vis) return false;

    // BFS için kuyruk (basit array)
    t_point queue[10000];
    int front = 0, rear = 0;
    
    // Başlangıç: P'den başla
    queue[rear++] = (t_point){m->py, m->px};
    vis[m->py][m->px] = true;
    
    int collected = 0;      // Kaç C topladık
    bool exit_found = false; // E'ye ulaşabildik mi
    
    // 4 yön: yukarı, aşağı, sol, sağ
    int dirs[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    
    // BFS döngüsü
    while (front < rear)
    {
        t_point cur = queue[front++];
        
        // Bu hücrede ne var?
        if (m->tiles[cur.y][cur.x] == T_COL)
            collected++;
        if (m->tiles[cur.y][cur.x] == T_EXIT)
            exit_found = true;
        
        // 4 yöne bak
        for (int d = 0; d < 4; d++)
        {
            int ny = cur.y + dirs[d][0];
            int nx = cur.x + dirs[d][1];
            
            // Sınır dışı mı?
            if (ny < 0 || nx < 0 || ny >= (int)m->rows || nx >= (int)m->cols)
                continue;
            
            // Zaten ziyaret edildi mi?
            if (vis[ny][nx])
                continue;
            
            // Duvar mı?
            if (m->tiles[ny][nx] == T_WALL)
                continue;
            
            // Eklemeye uygun
            vis[ny][nx] = true;
            queue[rear++] = (t_point){ny, nx};
        }
    }
    
    free_visited(vis, m->rows);
    
    // Tüm C'leri topladık mı VE E'ye ulaşabildik mi?
    return (collected == m->count_c && exit_found);
}