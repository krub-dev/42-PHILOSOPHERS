# Program
NAME = philo

# Flags
CFLAGS = -Wall -Werror -Wextra -lpthread

# Valgrind options for leak check
# VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

# Directories
SRC_DIR = SRC
INC_DIR = INCLUDE

# Colors
RESET = \033[0m
GREEN = \033[0;32m
RED = \033[0;31m

# Sources
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/utils.c $(SRC_DIR)/monitor.c $(SRC_DIR)/cleanup.c $(SRC_DIR)/routine.c $(SRC_DIR)/init.c

# Objects
OBJS = $(SRCS:.c=.o)

# Headers
HDRS = $(INC_DIR)/philosophers.h

# Default rule
all: $(NAME)

# Compile the executable
$(NAME): $(OBJS) Makefile
	@echo "$(GREEN)| Compiling >>> [$@] |$(RESET)"
	@cc $(CFLAGS) -I$(INC_DIR) $(OBJS) -o $(NAME)
	@echo "$(GREEN)| Completed >>> [$@] |$(RESET)"

# Generate objects (.o)
%.o: %.c $(HDRS)
	@cc $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Clean objects (.o)
clean:
	@rm -f $(OBJS)
	@echo "$(RED)| Objects cleaned |$(RESET)"

# Clean everything, including the executable
fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)| Everything cleaned |$(RESET)"

# Rebuild everything
re: fclean all

# Check for memory leaks with valgrind
leaks: $(NAME)
	@echo "$(GREEN)| Running memory leak check... |$(RESET)"
	@$(VALGRIND) ./$(NAME) 4 410 200 200 5
	@echo "$(GREEN)| Memory leak check completed |$(RESET)"

# Mark tasks as phony to avoid conflicts with existing files
.PHONY: all clean fclean re leaks
