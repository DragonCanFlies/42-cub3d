# =======================
# Program name
# =======================
NAME		= cub3D

# =======================
# Compiler and flags
# =======================
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
MATHFLAGS	= -lm

# =======================
# MinilibX (Linux)
# =======================
MLX_DIR		= mlx
MLX_LIB		= $(MLX_DIR)/libmlx.a
# Linux
# MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11
# macOS
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

# =======================
# Libft
# =======================
LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

# =======================
# Includes
# =======================
INCLUDES	= -I. -I$(MLX_DIR) -I$(LIBFT_DIR)

# =======================
# Source files
# =======================
SRCS		= cub3d.c \
			  raycaster.c \
			  utils_math.c \
			  input/cleanup.c \
			  input/colors_helpers.c \
			  input/errors.c \
			  input/normalize_map.c \
			  input/parse_config.c \
			  input/parse_map_helpers.c \
			  input/parse_map.c \
			  input/player_data.c \
			  input/textures_colors_helpers.c \
			  input/textures_colors.c \
			  load_textures.c \
			  texture.c

# =======================
# Object files
# =======================
OBJS		= $(SRCS:.c=.o)

# =======================
# Headers
# =======================
HEADERS		= cub3d.h input.h

# =======================
# Colors
# =======================
GREEN		= \033[0;32m
RED			= \033[0;31m
RESET		= \033[0m

# =======================
# Rules
# =======================
all: $(LIBFT) $(MLX_LIB) $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) $(MATHFLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) created successfully!$(RESET)"

%.o: %.c $(HEADERS)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# =======================
# Libft rule
# =======================
$(LIBFT):
	@echo "$(GREEN)Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)

# =======================
# MinilibX rule
# =======================
$(MLX_LIB):
	@echo "$(GREEN)Building MinilibX...$(RESET)"
	@$(MAKE) -C $(MLX_DIR)

# =======================
# Cleaning
# =======================
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
