// include/game.h
#ifndef GAME_H
# define GAME_H

# include "map.h"

typedef struct s_img { void *ptr; int w, h; } t_img;
typedef struct s_tex { t_img wall, floor, player, col, exit; } t_tex;

typedef struct s_app {
    void   *mlx;
    void   *win;
    int     moves;
    t_tex   tex;
    t_map  *map;
} t_app;

t_app *app(void);

#endif
