/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 19:15:25 by latabagl          #+#    #+#             */
/*   Updated: 2026/04/05 17:31:05 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <X11/keysym.h>
# include <sys/time.h>

# define WIN_WIDTH	1200
# define WIN_HEIGHT	800
# define MAP_S		64
# define FOV		60
# define RAY_ACC	0.1
# define MOVE_SPEED	3
# define ROT_SPEED	2
# define PLAYER_RADIUS 20  // PLAYER_RADIUS must be < than MOVE_SPEED
# define SHADE 0.5
# define MINIMAP_S 8

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
# define EXTRA_INFO "Extra info after identifier and path/rgb.\n"
# define NO_MAP "A map must be provided in the file.\n"
# define EMPTY_LINE_IN_MAP "Empty lines inside the map are forbidden.\n"
# define INVALID_CHAR_MAP "Map can only contain 0, 1, N, S, W or E\n"
# define ONLY_ONE_PLAYER "There are several player starting positions.\n"
# define NO_PLAYER "No player starting position.\n"
# define INCOMPLETE_FILE "Information missing : we need all textures,\
ceiling and floor colors and then the map.\n"
# define COLOR "There must be 3 colors, each one from 0 to 255.\n"
# define ERR_PPR \
"Warning PIXELS_PER_RAY is not a whole number. Change window size or RAY_ACC.\n"
# define CLOSED_MAP "The map must be closed/surrounded by walls.\n"

typedef struct s_door
{
	int	x;
	int	y;
	int	open;
}				t_door;

typedef struct s_tp
{
	int	enabled;
	int	just_teleported;
	int	ax;
	int	ay;
	int	bx;
	int	by;
}				t_tp;

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
	int		x;
	int		y;
	int		*map_data;
	t_door	*doors;
	int		doors_nb;
	t_tp	tp;
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
	float	map_scale;
}			t_img;

typedef struct s_ray
{
	int		index;
	float	ra;
	float	rx;
	float	ry;
	float	xo;
	float	yo;
	float	v_hit_x;
	float	v_hit_y;
	float	h_hit_x;
	float	h_hit_y;
	float	dis_v;
	float	dis_h;
	float	tan_val;
	int		dof;
	int		mx;
	int		my;
	int		mp;
}			t_ray;

typedef enum e_wall_dir
{
	N,
	S,
	E,
	W
}				t_wall_dir;

typedef struct s_wall
{
	int			line_h;
	int			line_offset;
	int			ca;
	int			color;
	float		x;
	float		y;
	float		dis;
	t_wall_dir	wall_dir;
	t_img		text;
	float		tx;
	float		ty;
	float		ty_step;
	float		ty_off;
}		t_wall;

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
	int	space;
}		t_keys;

typedef struct s_mouse
{
	int	x;
	int	initialized;
}				t_mouse;

typedef struct s_tex
{
	int			floor;
	int			ceiling;
	t_img		north;
	t_img		south;
	t_img		east;
	t_img		west;
	t_img		door;
}				t_tex;

//BONUS
/* ========== SPRITE SYSTEM  ========== */

typedef struct s_sprite
{
	float	x;
	float	y;
	float	dist;
	int		tex_id;
	int		type;
	int		alive;
	int		health;
	int		max_health;
}	t_sprite;

typedef struct s_spr_draw
{
	float	ray_x;
	float	dist_y;
	int		scr_x;
	int		height;
	int		width;
}	t_spr_draw;

typedef struct s_spr_bounds
{
	int	start_x;
	int	end_x;
	int	start_y;
	int	end_y;
}	t_spr_bounds;

// Gun system
/*
** Frame 0 (idle)
** Frame 1 (transition to firing)
** Frames 2-3 (cycle while shooting)
** Frame 4 (transition back to idle)
*/
typedef enum e_gun_state
{
	GUN_IDLE,
	GUN_FIRE_START,
	GUN_FIRING,
	GUN_FIRE_END
}	t_gun_state;

typedef struct s_gun
{
	t_img		frames[5]; // 5 frames now (not 4!)
	int			current_frame; // Which frame (0-4)
	t_gun_state	state; // Current animation state
	int			ammo;
	float		timer;
	float		fire_cooldown;
	int			active;
	float		anim_timer;
}	t_gun;

typedef struct s_gun_draw
{
	t_img	*tex;
	int		gun_w;
	int		gun_h;
	int		x;
	int		y;
}	t_gun_draw;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_player	player;
	t_keys		keys;
	t_mouse		mouse;
	t_map		map;
	t_tex		tex;
	float		px_per_ray;
		/* BONUS */
	t_sprite	*sprites;
	int			sprite_count;
	t_img		spr_tex[6]; // 4 ghost frames + 1 fruit + 1 food
	float		*zbuffer;
	int			collectibles;
	float		delta_time;
	float		last_time;
	t_gun		gun;
	int			health;
	int			max_health;
	float		damage_cooldown;

	float		max_sprite_size;
	float		inv_ray_acc;
	float		rad_to_deg;
	float		half_fov;
}				t_game;

// Constants
# define GUN_DURATION 12.0
# define FIRE_RATE 0.05f      // 200ms between shots = 5/sec
# define AMMO_PER_FRUIT 100
# define ENEMY_MAX_HEALTH 10
# define GUN_ANIM_SPEED 0.03  // 20 FPS for smooth firing

/* ========== SPRITE TYPES ========== */
# define TYPE_ENEMY 0
# define TYPE_FRUIT 1
# define TYPE_FOOD 2

/* ========== TEXTURE IDS (for sprites) ========== */
# define TEX_GHOST1 0
# define TEX_GHOST2 1
# define TEX_GHOST3 2
# define TEX_GHOST4 3
# define TEX_FRUIT 4
# define TEX_FOOD 5

/* ========== SPRITE CONSTANTS ========== */
# define MAX_SPRITES 100
# define ENEMY_SPEED 1.5f
# define E_ANIM_SPEED 0.2f
# define MIN_SPRITE_DIST 10.0f

# define PLAYER_MAX_HEALTH 100
# define ENEMY_DAMAGE 20
# define DAMAGE_COOLDOWN 1.0f  // 1 second invincibility after taking damage

# define HUD_OFFSET 20

// Libft
void	ft_bzero(void *s, size_t n);
void	ft_putstr_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);
char	*ft_itoa(int n);

// Key_hooks
int		close_window(t_game *game);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		mouse_move(int x, int y, t_game *game);

// Setup_hooks
void	setup_hooks(t_game *g);

// Init
void	init_game(t_game *g);
int		load_texture(char *path, t_img *texture, t_game *g);
int		rgb_to_int(uint8_t *colors_input);
void	destroy_textures(t_game *g);
void	init_texture(t_game *g);

// Render
void	put_pixel(t_img *img, int x, int y, int color);
void	draw_line(t_img *img, t_line *l, int color);
t_line	init_line(int x1, int y1, int x2, int y2);
int		render(t_game *game);
void	apply_texture(t_game *g, t_ray *ray, t_wall *wall);
void	get_wall_orientation(t_game *g, t_ray *ray, t_wall *wall);
void	check_boundaries(t_wall *wall);
void	assign_door_texture(t_game *g, t_ray *ray, t_wall *wall);

// Player
void	update_player(t_game *game);
void	rotate_player(t_game *game, float rotation);

// Raycaster
void	check_vertical(t_ray *ray, t_game *g);
void	check_horizontal(t_ray *ray, t_game *g);
void	ray_caster(t_game *game);

// Parser
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
void	ensure_closed_map(t_game *g);
void	parse_doors(t_game *g);
void	parse_tp(t_game *g);

// Utils
void	clean_map(t_map *map);
int		extract_color(char *str, int *i);
int		handle_rgb(uint8_t	colors[3], char *str);
void	print_error(char *msg);
void	handle_error(char *msg);
void	clean_exit(char *msg, t_map *map, char *line, int fd);
void	clean_exit_no_msg(t_map *map, char *line, int fd);
void	perror_exit(const char *message);
void	clean_exit_game(t_game *g);

// Utils_math
float	deg_to_rad(float angle);
float	fix_angle(float angle);

// Doors, tp, minimap
void	interact_with_door(t_game *g);
void	handle_teleportation(t_game *g);
void	draw_minimap(t_game *g);

// Sprite functions
void	init_sprites(t_game *g);
void	load_sprite_tex(t_game *g);
void	add_sprite(t_game *g, float x, float y, int type);
void	parse_sprites(t_game *g);
void	update_sprites(t_game *g);
void	render_sprites(t_game *g);
void	calc_spr_dist(t_game *g);
void	sort_sprites(t_game *g);
void	draw_sprite(t_game *g, t_sprite *s);
void	update_enemies(t_game *g);
void	move_enemy(t_game *g, t_sprite *e);
void	animate_enemy(t_game *g, t_sprite *enemy);
void	check_collectibles(t_game *g);
void	player_shoot(t_game *g);
void	update_delta_time(t_game *g);
float	calc_dist_to_player(t_game *g, t_sprite *s);
void	destroy_sprites_tex(t_game *g);
void	load_gun_tex(t_game *g);

// Sprite drawing helpers
void	transform_sprite(t_game *g, t_sprite *s, t_spr_draw *d);
void	draw_sprite_cols(t_game *g, t_sprite *s, t_spr_draw *d,
			t_spr_bounds *b);
int		get_spr_pixel(t_img *tex, int x, int y);
int		calc_tex_x(int x, t_spr_draw *d, int tex_w);
int		calc_tex_y(int y, t_spr_draw *d, int tex_h);
int		is_transparent(int color);
int		check_zbuffer(t_game *g, int x, float dist);

// Gun
void	init_gun(t_game *g);
void	render_gun_hud(t_game *g);
void	render_gun(t_game *g);
void	update_gun(t_game *g);
void	animate_gun(t_gun *gun);
void	load_gun_tex(t_game *g);
void	render_player_hud(t_game *g);

#endif
