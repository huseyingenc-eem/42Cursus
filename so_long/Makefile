# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/22 00:00:00 by hgenc             #+#    #+#              #
#    Updated: 2025/10/22 17:52:14 by hgenc            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= so_long

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I./include

BUILD_DIR	= build

SRCS		= src/main.c \
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

OBJS		= $(SRCS:%.c=$(BUILD_DIR)/%.o)

all: $(NAME)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "Compiled: $<"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "✅ $(NAME) created successfully!"

clean:
	@rm -rf $(BUILD_DIR)
	@echo "🧹 Object files cleaned"

fclean: clean
	@rm -f $(NAME)
	@echo "🧹 $(NAME) removed"

re: fclean all

.PHONY: all clean fclean re