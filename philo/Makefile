# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/19 18:40:03 by ccarro-d          #+#    #+#              #
#    Updated: 2025/08/19 20:36:41 by ccarro-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Exit
NAME = philo

# Folders
SRC_DIR = src
OBJ_DIR = obj

# Sources
SRC = 	$(SRC_DIR)/main.c 		\
		$(SRC_DIR)/philo.c 		\
		$(SRC_DIR)/monitor.c	\
		$(SRC_DIR)/inits.c		\
		$(SRC_DIR)/time.c		\
		$(SRC_DIR)/utils.c		\
		$(SRC_DIR)/clean.c

# Archivos objeto (en /obj)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Compilation
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread

# Build the executable
$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "✅ Compilation finished!"

# Recompile object files if philo.h changes
$(OBJ): philo.h

# Default target for compilation
all: $(NAME)

# Compile object files
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Compilation fo every .c to .o in /obj
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Create  /obj folder if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Clean objects (remove /obj folder)
clean:
	@rm -rf $(OBJ_DIR)
	@echo "🧹 Objects cleaned!"

# Clean objects and executable
fclean: clean
	@rm -f $(NAME)
	@echo "🧹 Executable cleaned!"

# Clean and recompile everything
re: fclean all

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
	valgrind --leak-check=full --show-leak-kinds=all

helgrind: all
	valgrind --tool=helgrind

# Key words
.PHONY: all clean fclean re asan tsan ubsan valgrind helgrind
