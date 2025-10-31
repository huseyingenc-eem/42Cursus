#ifndef RENDER_H
# define RENDER_H

# define TILE    64
# define VIEW_W  40
# define VIEW_H  30

# include <stdbool.h>

bool	init_window(void);
bool	load_textures(void);
void	first_draw(void);
void	redraw(void);

#endif
