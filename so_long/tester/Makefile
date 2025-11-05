NAME = test_runner

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = test_runner.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "✅ Test runner compiled successfully!"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: all
	@echo ""
	@echo "Running tests..."
	@echo ""
	@./$(NAME)

leaks: all
	@echo ""
	@echo "Running tests with memory leak detection..."
	@echo ""
	@./$(NAME) --leaks

.PHONY: all clean fclean re test leaks
