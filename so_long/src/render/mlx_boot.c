#include "../../include/game.h"
#include "../../include/render.h"
#include "../../include/camera.h"
#include "../../include/map.h"

bool    init_window(void)
{
    t_app   *a;
    int     win_w;
    int     win_h;

    a = app();
    camera_setup_viewport(a->map, VIEW_W, VIEW_H);
    
    // tile_size texture yükleme sırasında belirlendi
    win_w = camera()->view_w * a->tile_size;
    win_h = camera()->view_h * a->tile_size;
    
    // MLX zaten game_start'ta initialize edildi
    a->win = mlx_new_window(a->mlx, win_w, win_h, "so_long");
    if (!a->win)
        return (false);
    return (true);
}