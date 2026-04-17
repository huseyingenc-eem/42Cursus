NAME	= philo

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -pthread 

SRC_DIR	= src
BUILD	= build

SRCS	= $(SRC_DIR)/main.c \
		  $(SRC_DIR)/parse.c \
		  $(SRC_DIR)/init.c \
		  $(SRC_DIR)/routine.c \
		  $(SRC_DIR)/actions.c \
		  $(SRC_DIR)/monitor.c \
		  $(SRC_DIR)/utils.c \
		  $(SRC_DIR)/cleanup.c

OBJS	= $(SRCS:$(SRC_DIR)/%.c=$(BUILD)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(BUILD)/%.o: $(SRC_DIR)/%.c include/philo.h
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
