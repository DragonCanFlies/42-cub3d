# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/14 00:00:00 by loasaad           #+#    #+#              #
#    Updated: 2026/04/19 17:12:07 by latabagl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= cub3D
CC				= cc
CFLAGS			= -Wall -Wextra -Werror
INCLUDES		= -Iinclude -Imlx
INCLUDES_BONUS	= -Ibonus/include -Imlx
MLX_DIR			= mlx
MLX_LIB			= $(MLX_DIR)/libmlx.a
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
#MLX_FLAGS		= -L$(MLX_DIR) -lmlx -lXext -lX11
MATH_FLAGS		= -lm
SRC_DIR			= src
OBJ_DIR			= obj
OBJ_DIR_BONUS	= obj_bonus
SRCS			= src/cub3d.c \
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
SRCS_BONUS		= bonus/src/cub3d.c \
				  bonus/src/raycaster/raycaster.c \
				  bonus/src/raycaster/check_walls.c \
				  bonus/src/render/render.c \
				  bonus/src/render/render_texture.c \
				  bonus/src/render/render_texture_helpers.c \
				  bonus/src/player/player_movement.c \
				  bonus/src/parser/closed_map.c \
				  bonus/src/parser/parse_input.c \
				  bonus/src/parser/parse_doors.c \
				  bonus/src/parser/parse_map.c \
				  bonus/src/parser/parse_tp.c \
				  bonus/src/parser/parse_player_data.c \
				  bonus/src/parser/parse_textures.c \
				  bonus/src/parser/utils_parse_map.c \
				  bonus/src/parser/utils_parse_textures.c \
				  bonus/src/parser/normalize_map.c \
				  bonus/src/init/init_game.c \
				  bonus/src/init/init_textures.c \
				  bonus/src/init/init_sprites_textures.c \
				  bonus/src/events/key_hooks.c \
				  bonus/src/events/setup_hooks.c \
				  bonus/src/utils/cleanup.c \
				  bonus/src/utils/colors_helpers.c \
				  bonus/src/utils/errors.c \
				  bonus/src/utils/utils_math.c \
				  bonus/src/libft/get_next_line.c \
				  bonus/src/libft/get_next_line_utils.c \
				  bonus/src/libft/libft.c \
				  bonus/src/bonus/door.c \
				  bonus/src/bonus/minimap.c \
				  bonus/src/bonus/tp.c \
				  bonus/src/libft/itoa.c \
				  bonus/src/sprites/sprite_init.c \
				  bonus/src/sprites/sprite_distance.c \
				  bonus/src/sprites/sprite_transform.c \
				  bonus/src/sprites/sprite_draw_utils.c \
				  bonus/src/sprites/sprite_draw.c \
				  bonus/src/sprites/sprite_render.c \
				  bonus/src/sprites/enemy_update.c \
				  bonus/src/sprites/enemy_move.c \
				  bonus/src/sprites/sprite_animate.c \
				  bonus/src/sprites/game_collectibles.c \
				  bonus/src/sprites/game_shoot.c \
				  bonus/src/gun/gun_animate.c \
				  bonus/src/gun/gun_init.c \
				  bonus/src/gun/gun_render.c \
				  bonus/src/gun/gun_update.c \
				  bonus/src/render/hud.c
OBJS			= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))
OBJS_BONUS		= $(patsubst %.c,$(OBJ_DIR_BONUS)/%.o,$(SRCS_BONUS))

GREEN			= \033[0;32m
RED				= \033[0;31m
YELLOW			= \033[0;33m
BLUE			= \033[0;34m
RESET			= \033[0m

all: $(MLX_LIB) $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) $(MATH_FLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) created successfully!$(RESET)"

bonus: $(MLX_LIB) $(OBJS_BONUS)
	@echo "$(YELLOW)Linking bonus...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(MLX_FLAGS) $(MATH_FLAGS) -o $(NAME)
	@echo "$(GREEN)Bonus build complete!$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR_BONUS)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling bonus $<$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES_BONUS) -c $< -o $@

$(MLX_LIB):
	@echo "$(YELLOW)Building MLX...$(RESET)"
	@make -C $(MLX_DIR) 2>/dev/null || make -C $(MLX_DIR)
	@echo "$(GREEN)MLX built successfully!$(RESET)"

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DIR_BONUS)
	@make -C $(MLX_DIR) clean 2>/dev/null || true
	@echo "$(GREEN)Clean complete!$(RESET)"

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)Full clean complete!$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus