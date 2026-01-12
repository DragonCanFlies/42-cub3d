/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:15:07 by latabagl          #+#    #+#             */
/*   Updated: 2026/01/12 01:39:52 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/ft_printf.h"

# include <stdio.h> // debug
# include <stdint.h> // uint8_t
# include <stdlib.h> // free, exit
# include <fcntl.h> // open
# include "cub3d.h"

# define ARG_NB_ERR "Invalid number of arguments\n"
# define INVALID_FILENAME "Map file must end with .cub\n"
# define OPEN_MAP "Map can't be opened.\n"
# define ID_DUPLICATA "Duplicate identifier found (NO, SO, WE, EA, C, F).\n"
# define NO_INFO "Identifier is not followed by any information.\n"
# define INVALID_ID "Identifier should be NO, SO, WE, EA, C or F\n"
# define MALLOC "Memory allocation failure.\n"
# define EXTRA_INFO "Identifier: path/RGB not respected.\n"
# define NO_MAP "A map must be provided in the file.\n"
# define EMPTY_LINE_IN_MAP "Empty lines inside the map are forbidden.\n"
# define INVALID_CHAR_MAP "Map can only contains 0, 1, N, S, W or E\n"
# define ONLY_ONE_PLAYER "There are several player starting positions.\n"
# define NO_PLAYER "No player starting position.\n"
# define INCOMPLETE_FILE "Information missing : we need all textures,\
	ceiling and floor colors and then the map.\n"
# define COLOR "There must be 3 colors, each one from 0 to 255.\n"

typedef enum e_id
{
	NO,
	SO,
	EA,
	WE,
	F,
	C
}				t_id;

typedef struct s_config_flags
{
	int	has_no;
	int	has_so;
	int	has_ea;
	int	has_we;
	int	has_f;
	int	has_c;
}				t_config_flags;

typedef struct s_config
{
	char	*north_path;
	char	*south_path;
	char	*east_path;
	char	*west_path;
	uint8_t	ceiling[3];
	uint8_t	floor[3];
	int		flag;
	char	**map;
	int		map_x; // nb of tiles
	int		map_y;
	int		*map_data; // map_data[y * map_x + x]
	int		player_x; // * MAP_S + MAP_S /2 to get coordinate
	int		player_y;
	float	player_angle;
}				t_config;

// input validation
void	parse_config(int argc, char **argv, t_config *config);
// textures and colors
char	*extract_walls_floor_ceiling(t_config *config,
			t_config_flags *config_flags, int fd);
// textures and colors helpers
void	skip_space_or_tab(char *line, int *i);
void	skip_token(char *line, int *i);
int		handle_config_flag(int *config_flag, int flag);
int		get_config_flag(char *line, int i, int j, t_config_flags *config_flags);
int		all_elements_except_map(t_config_flags *config_flags);
int		extract_color(char *str, int *i);
int		handle_rgb(uint8_t	colors[3], char *str);
// parse map
void	parse_map(t_config *config, int fd, char *line);
// parse map helpers
int		is_empty_line(char *line);
char	*skip_empty_lines(t_config *config, int fd, char *line);
int		has_valid_characters(char *line, int *player_found);
// normalize map
void	normalize_map(t_config *config);
// player
void	get_player_data(t_config *config);
// errors
void	handle_error(char *msg);
void	print_error(char *msg);
void	clean_exit(char *msg, t_config *config, char *line, int fd);
void	clean_exit_no_msg(t_config *config, char *line, int fd);
// cleanup
void	clean_config(t_config *t_config);

// debug
void	print_config(t_config *config);

#endif