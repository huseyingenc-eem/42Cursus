// src/render/mlx_init.c (her fonksiyon <25 satır olsun)
#include "../../include/game.h"
#include "../../include/utils.h"


t_app *app(void){ static t_app g; return &g; }

bool game_start(t_map *m){
    t_app *a = app();
    a->map = m;
    a->mlx = mlx_init();
    if (!a->mlx) return false;
    a->win = mlx_new_window(a->mlx, m->cols*TILE, m->rows*TILE, "so_long");
    if (!a->win) return false;
    return texture_load() && hooks_install() && first_draw();
}
