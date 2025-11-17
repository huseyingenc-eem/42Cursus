CC      := cc
CFLAGS  := -Wall -Wextra -Werror
INCDIR  := include
INCS    := -I$(INCDIR)


SERVER      := server
CLIENT      := client
SERVER_B    := server_bonus
CLIENT_B    := client_bonus


SRCDIR      := src
SRCS_COMMON := $(SRCDIR)/utils.c

SRCS_SERVER := $(SRCDIR)/server.c   $(SRCS_COMMON)
SRCS_CLIENT := $(SRCDIR)/client.c   $(SRCS_COMMON)

SRCDIR_B    := src_bonus
SRCS_SERVER_B := $(SRCDIR_B)/server_bonus.c $(SRCS_COMMON)
SRCS_CLIENT_B := $(SRCDIR_B)/client_bonus.c $(SRCS_COMMON)


OBJDIR      := build
OBJS_SERVER := $(SRCS_SERVER:%.c=$(OBJDIR)/%.o)
OBJS_CLIENT := $(SRCS_CLIENT:%.c=$(OBJDIR)/%.o)
OBJS_SERVER_B := $(SRCS_SERVER_B:%.c=$(OBJDIR)/%.o)
OBJS_CLIENT_B := $(SRCS_CLIENT_B:%.c=$(OBJDIR)/%.o)

.PHONY: all bonus clean fclean re

all: $(SERVER) $(CLIENT)

bonus: $(SERVER_B) $(CLIENT_B)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) $(INCS) $^ -o $@

$(CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $(INCS) $^ -o $@

$(SERVER_B): $(OBJS_SERVER_B)
	$(CC) $(CFLAGS) $(INCS) $^ -o $@

$(CLIENT_B): $(OBJS_CLIENT_B)
	$(CC) $(CFLAGS) $(INCS) $^ -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(SERVER) $(CLIENT) $(SERVER_B) $(CLIENT_B)

re: fclean all
