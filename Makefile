# Exit
NAME = philo

# Compilation
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread #-g #-fsanitize=thread	 #valgrind --tool=helgrind

# Sources
SRC = main.c philo.c utils.c inits.c clean.c monitor.c debug.c time.c

OBJS = $(SRC:.c=.o)

# Build the executable
$(NAME): $(OBJS) 
	@$(CC) $(OBJS) -o $(NAME)
	@echo "✅ Compilation finished!"

# Recompile object files if philo.h changes
$(OBJS): philo.h

# Default target for compilation
all: $(NAME)

# Compile object files
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean objects
clean:
	@rm -f $(OBJS)
	@echo "🧹 Objects cleaned!"

# Clean objects and executable
fclean: clean
	@rm -f $(NAME)
	@echo "🧹 Executable cleaned!"

# Clean and recompile everything
re: fclean all

# Key words
.PHONY: all clean fclean re
