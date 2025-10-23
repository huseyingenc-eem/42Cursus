#include "../../include/map.h"
#include "../../include/utils.h"
#include <stdlib.h>
#include <string.h>

typedef struct s_point {
    int y;
    int x;
} t_point;

static bool **alloc_visited(size_t rows, size_t cols)
{
    bool **vis;
    size_t r;
    
    // Çok büyük haritaları reddet
    if (rows > 2000 || cols > 2000)
        return NULL;
    
    vis = malloc(sizeof(bool *) * rows);
    if (!vis) 
        return NULL;
    
    // Başlangıçta NULL'la
    for (r = 0; r < rows; r++)
        vis[r] = NULL;
    
    for (r = 0; r < rows; r++)
    {
        vis[r] = malloc(sizeof(bool) * cols);
        if (!vis[r])
        {
            // Hata durumunda önceki satırları temizle
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
    size_t r;
    
    if (!vis) 
        return;
    for (r = 0; r < rows; r++)
        free(vis[r]);
    free(vis);
}

bool validate_map_reachable(const t_map *m)
{
    bool **vis;
    t_point *queue;
    int front = 0, rear = 0;
    int collected = 0;
    bool exit_found = false;
    int dirs[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    size_t queue_size;
    
    ft_printf("Pathfinding for %zu x %zu map...\n", m->rows, m->cols);
    
    // Büyük haritalar için daha büyük kuyruk
    queue_size = m->rows * m->cols;
    if (queue_size > 1000000) // 1M'den büyükse reddet
    {
        ft_printf("Error: Map too large for pathfinding\n");
        return false;
    }
    
    vis = alloc_visited(m->rows, m->cols);
    if (!vis)
    {
        ft_printf("Error: Cannot allocate visited array\n");
        return false;
    }
    
    queue = malloc(sizeof(t_point) * queue_size);
    if (!queue)
    {
        free_visited(vis, m->rows);
        ft_printf("Error: Cannot allocate queue\n");
        return false;
    }
    
    // Başlangıç: P'den başla
    queue[rear++] = (t_point){m->py, m->px};
    vis[m->py][m->px] = true;
    
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
            
            // Kuyruk doldu mu?
            if (rear >= (int)queue_size)
            {
                ft_printf("Error: Queue overflow in pathfinding\n");
                free(queue);
                free_visited(vis, m->rows);
                return false;
            }
            
            // Eklemeye uygun
            vis[ny][nx] = true;
            queue[rear++] = (t_point){ny, nx};
        }
    }
    
    free(queue);
    free_visited(vis, m->rows);
    
    ft_printf("Pathfinding complete: %d/%d collectibles, exit=%s\n", 
             collected, m->count_c, exit_found ? "yes" : "no");
    
    // Tüm C'leri topladık mı VE E'ye ulaşabildik mi?
    return (collected == m->count_c && exit_found);
}