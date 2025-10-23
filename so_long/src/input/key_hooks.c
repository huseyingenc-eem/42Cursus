#include "../../include/input.h"
#include "../../include/game.h"

int on_key_pressed(int keycode, void *ctx)
{
    (void)ctx;
    if (keycode == KEY_ESC)
    {
        game_cleanup();
        exit(0);
    }
    else if (keycode == KEY_W)
        move_up();
    else if (keycode == KEY_S)
        move_down();
    else if (keycode == KEY_A)
        move_left();
    else if (keycode == KEY_D)
        move_right();
    return (0);
}

int on_window_close(void *ctx)
{
    (void)ctx;
    game_cleanup();
    exit(0);
    return (0);
}