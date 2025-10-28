NAME    := so_long
CC      := cc
CFLAGS  := -Wall -Wextra -Werror
INCS    := -Iinclude -Imlx

MLX_DIR := mlx
MLX_LIB := $(MLX_DIR)/libmlx_Linux.a
MLX_LDF := -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz

BUILD_DIR := build

SRCS := \
    src/main.c \
    src/core/app.c \
    src/core/game_start.c \
    src/core/game_loop.c \
    src/core/game_cleanup.c \
    src/input/key_hooks.c \
    src/input/move_player.c \
    src/render/camera.c \
    src/render/mlx_boot.c \
    src/render/draw_map.c \
    src/render/draw_hud.c \
    src/render/texture_load.c \
    src/map/map_load.c \
    src/map/map_validate.c \
    src/map/path_check.c \
    src/map/map_free.c \
    src/utils/error_exit.c \
    src/utils/str_utils.c \
    src/utils/read_file.c \
    src/utils/split_lines.c \
    src/utils/path_utils.c \
    src/utils/ft_printf.c

OBJS := $(SRCS:src/%.c=$(BUILD_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LDF) -o $(NAME)

$(BUILD_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re