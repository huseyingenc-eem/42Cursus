NAME		= push_swap
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

SRCDIR		= src
INCDIR		= include
BUILDDIR	= build

SRCS		= $(SRCDIR)/main.c \
			  $(SRCDIR)/utils.c \
			  $(SRCDIR)/utils2.c \
			  $(SRCDIR)/operations/ops_push.c \
			  $(SRCDIR)/operations/ops_reverse_rotate.c \
			  $(SRCDIR)/operations/ops_rotate.c \
			  $(SRCDIR)/operations/ops_swap.c \
			  $(SRCDIR)/parse/parse.c \
			  $(SRCDIR)/parse/parse_utils.c \
			  $(SRCDIR)/solver/normalize.c \
			  $(SRCDIR)/solver/small_sort.c \
			  $(SRCDIR)/solver/solver_radix.c \
			  $(SRCDIR)/stack/memory.c \
			  $(SRCDIR)/stack/stack.c

OBJS		= $(SRCS:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)

HEADERS		= $(INCDIR)/push_swap.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	$(RM) -r $(BUILDDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
