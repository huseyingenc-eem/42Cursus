#ifndef RENDER_H
# define RENDER_H

# define TILE    64
# define VIEW_W  30
# define VIEW_H  20

struct s_app;

int		init_window(struct s_app *a);
int		load_textures(struct s_app *a);
void	first_draw(struct s_app *a);
void	redraw(struct s_app *a);

#endif
