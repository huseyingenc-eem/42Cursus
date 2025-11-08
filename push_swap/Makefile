CC       := cc
CFLAGS   := -Wall -Wextra -Werror
INCS     := -I include
DEPFLAGS := -MMD -MP

NAME      := push_swap

BUILD_DIR := build

SRCS := \
	src/main.c \
	src/parse.c \
	src/normalize.c \
	src/stack.c \
	src/ops.c \
	src/small_sort.c \
	src/solver_radix.c \
	src/utils.c \
	src/memory.c

OBJS := $(addprefix $(BUILD_DIR)/,$(SRCS:.c=.o))
DEPS := $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(DEPFLAGS) $(INCS) -c $< -o $@

clean:
	@rm -rf $(BUILD_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
