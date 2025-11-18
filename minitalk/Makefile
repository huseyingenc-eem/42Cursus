CC      = cc
CFLAGS  = -Wall -Wextra -Werror
RM      = rm -f

INCDIR  = include
SRCDIR  = src
SRCDIR_B= src_bonus
OBJDIR  = build

INCS    = -I$(INCDIR)

NAME            = server
CLIENT          = client
NAME_BONUS      = server_bonus
CLIENT_BONUS    = client_bonus

SRCS_SERVER     = $(SRCDIR)/server.c
SRCS_CLIENT     = $(SRCDIR)/client.c
SRCS_UTILS      = $(SRCDIR)/utils.c

SRCS_SERVER_B   = $(SRCDIR_B)/server_bonus.c
SRCS_CLIENT_B   = $(SRCDIR_B)/client_bonus.c
SRCS_UTILS_B    = $(SRCDIR_B)/utils_bonus.c

OBJS_SERVER     = $(OBJDIR)/server.o $(OBJDIR)/utils.o
OBJS_CLIENT     = $(OBJDIR)/client.o $(OBJDIR)/utils.o

OBJS_SERVER_B   = $(OBJDIR)/server_bonus.o $(OBJDIR)/utils_bonus.o
OBJS_CLIENT_B   = $(OBJDIR)/client_bonus.o $(OBJDIR)/utils_bonus.o

.PHONY: all bonus clean fclean re

all: $(NAME) $(CLIENT)

bonus: $(NAME_BONUS) $(CLIENT_BONUS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(OBJDIR)/%_bonus.o: $(SRCDIR_B)/%_bonus.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(NAME): $(OBJS_SERVER)
	$(CC) $(CFLAGS) $(INCS) $^ -o $@

$(CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $(INCS) $^ -o $@

$(NAME_BONUS): $(OBJS_SERVER_B)
	$(CC) $(CFLAGS) $(INCS) $^ -o $@

$(CLIENT_BONUS): $(OBJS_CLIENT_B)
	$(CC) $(CFLAGS) $(INCS) $^ -o $@

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME) $(CLIENT) $(NAME_BONUS) $(CLIENT_BONUS)

re: fclean all
