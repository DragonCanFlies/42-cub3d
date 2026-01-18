# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/14 00:00:00 by loasaad           #+#    #+#              #
#    Updated: 2026/01/18 15:22:33 by latabagl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

# Compiler and flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -Iinclude -Imlx

# MLX settings
MLX_DIR		= mlx
MLX_LIB		= $(MLX_DIR)/libmlx.a
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
# MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11
MATH_FLAGS	= -lm

# Directories
SRC_DIR		= src
OBJ_DIR		= obj

# Source files with paths
SRCS		= src/cub3d.c \
			  src/raycaster/raycaster.c \
			  src/raycaster/check_walls.c \
			  src/render/render.c \
			  src/render/render_texture.c \
			  src/render/render_texture_helpers.c \
			  src/player/player_movement.c \
			  src/parser/closed_map.c \
			  src/parser/parse_input.c \
			  src/parser/parse_map.c \
			  src/parser/parse_player_data.c \
			  src/parser/parse_textures.c \
			  src/parser/utils_parse_map.c \
			  src/parser/utils_parse_textures.c \
			  src/parser/normalize_map.c \
			  src/init/init_game.c \
			  src/init/init_textures.c \
			  src/events/key_hooks.c \
			  src/events/setup_hooks.c \
			  src/utils/cleanup.c \
			  src/utils/colors_helpers.c \
			  src/utils/errors.c \
			  src/utils/utils_math.c \
			  src/libft/get_next_line.c \
			  src/libft/get_next_line_utils.c \
			  src/libft/libft.c

# Object files - use patsubst for correct path handling
OBJS		= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

# Colors
GREEN		= \033[0;32m
RED			= \033[0;31m
YELLOW		= \033[0;33m
BLUE		= \033[0;34m
RESET		= \033[0m

# Rules
all: $(MLX_LIB) $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) $(MATH_FLAGS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) created successfully!$(RESET)"

# Create object directories and compile
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(MLX_LIB):
	@echo "$(YELLOW)Building MLX...$(RESET)"
	@make -C $(MLX_DIR) 2>/dev/null || make -C $(MLX_DIR)
	@echo "$(GREEN)✓ MLX built successfully!$(RESET)"

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make -C $(MLX_DIR) clean 2>/dev/null || true
	@echo "$(GREEN)✓ Clean complete!$(RESET)"

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)✓ Full clean complete!$(RESET)"

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus