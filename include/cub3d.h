#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "get_next_line.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdint.h> // uint8_t

# define WIN_WIDTH	1280
# define WIN_HEIGHT	720
# define MAP_S		64
# define FOV		60
# define RAY_ACC	0.1
# define MOVE_SPEED	3
# define ROT_SPEED	2

# define KEY_W		13
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2
# define KEY_ESC	53
# define KEY_LEFT 	123
# define KEY_RIGHT	124

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
# define INVALID_CHAR_MAP "Map can only contain 0, 1, N, S, W or E\n"
# define ONLY_ONE_PLAYER "There are several player starting positions.\n"
# define NO_PLAYER "No player starting position.\n"
# define INCOMPLETE_FILE "Information missing : we need all textures,\
	ceiling and floor colors and then the map.\n"
# define COLOR "There must be 3 colors, each one from 0 to 255.\n"
# define ERR_PPR "Warning PIXELS_PER_RAY is not a whole number. Change window size or RAY_ACC"

typedef enum e_id
{
	NO,
	SO,
	EA,
	WE,
	F,
	C
}				t_id;

typedef struct s_map_flags
{
	int	has_no;
	int	has_so;
	int	has_ea;
	int	has_we;
	int	has_f;
	int	has_c;
}				t_map_flags;

typedef struct s_map
{
	char	*north_path;
	char	*south_path;
	char	*east_path;
	char	*west_path;
	uint8_t	ceiling[3];
	uint8_t	floor[3];
	int		current_id;
	char	**raw_map;
	int		x; // nb of tiles
	int		y;
	int		*map_data; // map_data[map_y * map_x + x]
}				t_map;

typedef struct s_line
{
	int	x1;
	int	x2;
	int	y1;
	int	y2;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}		t_line;

typedef struct s_img
{
	void	*img;
	char	*buffer;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
	// float	inv_map_scale;
}			t_img;


typedef struct s_ray
{
	int		index;		// RAY index
	float	ra;         // Ray angle
	float	rx;         // Ray X position
	float	ry;         // Ray Y position
	float	xo;         // X offset (step size)
	float	yo;         // Y offset (step size)
	float	v_hit_x;    // Vertical hit X
	float	v_hit_y;    // Vertical hit Y
	float	h_hit_x;    // horizontal hit X
	float	h_hit_y;    // horizontal hit Y
	float	dis_v;      // Vertical distance
	float	dis_h;      // Horizontal distance
	float	tan_val;    // Tangent value
	int		dof;        // Depth of field
	int		mx;         // Map X coordinate
	int		my;         // Map Y coordinate
	int		mp;         // Map position (array index)
}			t_ray;

typedef enum	e_wall_dir
{
	N,
	S,
	E,
	W
}				t_wall_dir;

typedef struct s_wall
{
	int			line_h;     // Wall height
	int			line_offset;   // Wall offset
	int			ca;         // Corrected angle
	int			color;      // Wall color. delete later?
	float		x;
	float		y;
	float		dis;
	int			text_h;
	t_wall_dir	wall_dir;
	t_img		text;
	float		tx; // text coordinates
	float		ty;
	float		ty_step;
	float		ty_off;
	// float		texture_scale; 
}		t_wall;


// *img is for mlx
// bpp = bits per pixel, usually 32


typedef struct s_player
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	angle;
}			t_player;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	esc;
	int	left;
	int	right;
}		t_keys;

typedef struct s_tex
{
	int			floor;
	int			ceiling;
	t_img		north;
	t_img		south;
	t_img		east;
	t_img		west;
}				t_tex;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_player	player;
	t_keys		keys;
	t_map		map;
	t_tex		tex;
	//int			map[MAP_X * MAP_Y];
	float			px_per_ray;
}				t_game;

//libft
void	ft_bzero(void *s, size_t n);
void	ft_putstr_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);

//events
	//key_hooks
int	close_window(t_game *game);
int	key_press(int keycode, t_game *game);
int	key_release(int keycode, t_game *game);

	//setup_hooks
void	setup_hooks(t_game *g);

//init
void	init_game(t_game *g);
int		load_texture(char *path, t_img *texture, t_game *g);
int		rgb_to_int(uint8_t *colors_input);
void	destroy_images(t_game *g);
void	init_texture(t_game *g);

//render
void	put_pixel(t_img *img, int x, int y, int color);
void	draw_rect(t_img *img, int x, int y, int w, int h, int color);
void	draw_line(t_img *img, t_line *l, int color);
t_line	init_line(int x1, int y1, int x2, int y2);
int	render(t_game *game);
void	apply_texture(t_game *g, t_ray *ray, t_wall* wall);

//player
void	update_player(t_game *game);

//raycaster
void	check_vertical(t_ray *ray, t_game *g);
void	check_horizontal(t_ray *ray, t_game *g);
void	ray_caster(t_game *game);

//parse
void	normalize_map(t_map *map);
void	parse_input(int argc, char **argv, t_game *g);
void	parse_map(t_map *map, int fd, char *line);
void	parse_player_data(t_game *g);
char	*parse_textures(t_map *map, t_map_flags *map_flags, int fd);
int		is_empty_line(char *line);
char	*skip_empty_lines(t_map *config, int fd, char *line);
int		has_valid_characters(char *line, int *player_found);
void	skip_space_or_tab(char *line, int *i);
void	skip_token(char *line, int *i);
int		handle_map_flag(int *map_flag, int flag);
int		get_map_flag(char *line, int i, int j, t_map_flags *flags);
int		textures_are_extracted(t_map_flags *flags);

//utils
void	clean_map(t_map *map);
int		extract_color(char *str, int *i);
int		handle_rgb(uint8_t	colors[3], char *str);
void	print_error(char *msg);
void	handle_error(char *msg);
void	clean_exit(char *msg, t_map *map, char *line, int fd);
void	clean_exit_no_msg(t_map *map, char *line, int fd);
void	perror_exit(const char *message);
	//utils_math
float	deg_to_rad(float angle);
float	fix_angle(float angle);


#endif
