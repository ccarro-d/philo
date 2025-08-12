# Exit
NAME = philo

# Compilation
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread

# Sources
SRC = 	main.c 		\
		philo.c 	\
		monitor.c	\
		inits.c		\
		time.c		\
		utils.c		\
		clean.c

OBJS = $(SRC:.c=.o)

# Build the executable
$(NAME): $(OBJS) 
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "✅ Compilation finished!"

# Recompile object files if philo.h changes
$(OBJS): philo.h

# Default target for compilation
all: $(NAME)

# Compile object files
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Sanitizer builds
asan:
	@$(MAKE) fclean
	@$(MAKE) $(NAME) CFLAGS="$(CFLAGS) -g -fsanitize=address"

tsan:
	@$(MAKE) fclean
	@$(MAKE) $(NAME) CFLAGS="$(CFLAGS) -g -fsanitize=thread"

ubsan:
	@$(MAKE) fclean
	@$(MAKE) $(NAME) CFLAGS="$(CFLAGS) -g -fsanitize=undefined"

# Valgrind / Helgrind runs (Linux only)
valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) 5 800 200 200

helgrind: all
	valgrind --tool=helgrind ./$(NAME) 5 800 200 200


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
.PHONY: all clean fclean re asan tsan ubsan valgrind helgrind
