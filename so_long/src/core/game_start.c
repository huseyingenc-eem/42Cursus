#include "../../include/game.h"
#include "../../include/render.h"
#include "../../include/input.h"
#include "../../include/camera.h"
#include "../../include/map.h"
#include "../../include/utils.h"

static void	install_hooks(void)
{
	t_app	*a;

	a = app();
	mlx_key_hook(a->win, &on_key_pressed, NULL);
	mlx_hook(a->win, 17, 0, &on_window_close, NULL);
}

int	game_start(t_map *map)
{
	t_app *a = app();
	
	a->map = map;
	a->tile_size = 0; // Başlangıçta sıfır
	
	// MLX'i başlat
	a->mlx = mlx_init();
	if (!a->mlx)
		return (0);
		
	// Texture'ları yükle (tile_size'ı belirleyecek)
	if (!load_textures())
		return (0);
		
	// Artık tile_size belli, window'u aç
	if (!init_window())
		return (0);
		
	/* oyuncuyu kadraja oturtup ilk çizim */
	camera_follow_with_deadzone(map, 10, 8);
	first_draw();
	install_hooks();
	mlx_loop(a->mlx);
	return (1);
}
