#include "../../include/camera.h"
#include "../../include/game.h"
#include "../../include/map.h"
#include "../../include/render.h"
#include "../../include/utils.h"
#include <stdlib.h>

static void	print_move_count(int moves)
{
    ft_printf("\033[H\033[2J");
    ft_printf("Moves: %d\n", moves);
}

static void	collect_item(t_app *a, int nx, int ny)
{
    if (a->map->tiles[ny][nx] == T_COL)
    {
        a->map->tiles[ny][nx] = T_EMPTY;
        a->map->count_c--;
        ft_printf("Collectibles remaining: %d\n", a->map->count_c);
    }
}

static void	check_exit(t_app *a, int nx, int ny)
{
    if (a->map->tiles[ny][nx] == T_EXIT)
    {
        if (a->map->count_c == 0)
        {
            ft_printf("\n🎉 YOU WIN! 🎉\n");
            ft_printf("Total moves: %d\n", a->moves);
            game_cleanup();
            exit(0);
        }
        else
        {
            ft_printf("⚠️  Collect all items first! (%d remaining)\n", 
                a->map->count_c);
        }
    }
}

static void	apply_move(int nx, int ny)
{
    t_app	*a;

    a = app();
    
    // Önce collectible topla (varsa)
    collect_item(a, nx, ny);
    
    // Sonra hareket et
    a->map->px = nx;
    a->map->py = ny;
    a->moves++;
    
    // Ekranı güncelle
    print_move_count(a->moves);
    redraw();
    
    // Exit kontrolü (hareket ettikten SONRA)
    check_exit(a, nx, ny);
}

void	move_up(void)
{
    t_app	*a;
    int		nx;
    int		ny;

    a = app();
    nx = a->map->px;
    ny = a->map->py - 1;
    if (ny >= 0 && a->map->tiles[ny][nx] != T_WALL)
        apply_move(nx, ny);
}

void	move_down(void)
{
    t_app	*a;
    int		nx;
    int		ny;

    a = app();
    nx = a->map->px;
    ny = a->map->py + 1;
    if (ny < (int)a->map->rows && a->map->tiles[ny][nx] != T_WALL)
        apply_move(nx, ny);
}

void	move_left(void)
{
    t_app	*a;
    int		nx;
    int		ny;

    a = app();
    nx = a->map->px - 1;
    ny = a->map->py;
    if (nx >= 0 && a->map->tiles[ny][nx] != T_WALL)
        apply_move(nx, ny);
}

void	move_right(void)
{
    t_app	*a;
    int		nx;
    int		ny;

    a = app();
    nx = a->map->px + 1;
    ny = a->map->py;
    if (nx < (int)a->map->cols && a->map->tiles[ny][nx] != T_WALL)
        apply_move(nx, ny);
}