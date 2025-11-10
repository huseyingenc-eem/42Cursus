NAME		= push_swap
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

SRCDIR		= src
INCDIR		= include
BUILDDIR	= build

SRCS		= $(SRCDIR)/main.c \
			  $(SRCDIR)/memory.c \
			  $(SRCDIR)/normalize.c \
			  $(SRCDIR)/ops_swap.c \
			  $(SRCDIR)/ops_push.c \
			  $(SRCDIR)/ops_rotate.c \
			  $(SRCDIR)/ops_reverse_rotate.c \
			  $(SRCDIR)/parse.c \
			  $(SRCDIR)/parse_utils.c \
			  $(SRCDIR)/small_sort.c \
			  $(SRCDIR)/small_sort_utils.c \
			  $(SRCDIR)/solver_radix.c \
			  $(SRCDIR)/stack.c \
			  $(SRCDIR)/utils.c \
			  $(SRCDIR)/utils2.c

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
