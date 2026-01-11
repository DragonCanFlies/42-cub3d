
# Program name
NAME		= cub3D

# Compiler and flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
MATHFLAGS	= -lm

# MinilibX
MLX_DIR		= mlx
MLX_LIB		= $(MLX_DIR)/libmlx.a

# macOS specific flags (comment out if on Linux)
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

# Linux specific flags (uncomment if on Linux)
# MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11

# Source files
SRCS		= cub3d.c \
			  raycaster.c \
			  utils_math.c

# Object files
OBJS		= $(SRCS:.c=.o)

# Header files
HEADERS		= cub3d.h

# Colors for output
GREEN		= \033[0;32m
RED			= \033[0;31m
RESET		= \033[0m

# Rules
all: $(MLX_LIB) $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) $(MATHFLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) created successfully!$(RESET)"

%.o: %.c $(HEADERS)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

$(MLX_LIB):
	@echo "$(GREEN)Building MinilibX...$(RESET)"
	@make -C $(MLX_DIR) 2>/dev/null || true

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -f $(OBJS)
	@make -C $(MLX_DIR) clean 2>/dev/null || true

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re