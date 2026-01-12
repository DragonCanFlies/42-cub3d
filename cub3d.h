#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdint.h> // uint8_t

# define WIN_WIDTH	1260 // multiple of px per ray
# define WIN_HEIGHT	510
# define MAP_S		64
# define FOV		60
# define RAY_ACC	1
# define MOVE_SPEED	3
# define ROT_SPEED	3

# define KEY_W		13
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2
# define KEY_ESC	53
# define KEY_LEFT 	123
# define KEY_RIGHT	124

typedef enum	e_wall_dir
{
	N,
	S,
	E,
	W
}				t_wall_dir;

typedef struct s_ray
{
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
	int		r;          // Ray number
	int		dof;        // Depth of field
	int		mx;         // Map X coordinate
	int		my;         // Map Y coordinate
	int		mp;         // Map position (array index)
}			t_ray;

typedef struct s_img
{
	void	*img;
	char	*buffer;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}			t_img;

typedef struct s_wall
{
	int			line_h;     // Wall height
	int			line_offset;   // Wall offset
	int			ca;         // Corrected angle
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
}		t_wall;


// *img is for mlx
// bpp = bits per pixel, usually 32

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

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_player	player;
	t_keys		keys;
	int			*map;
	int			px_per_ray;
	int			map_x;
	int			map_y;
	int			floor;
	int			ceiling;
	t_img		north;
	t_img		south;
	t_img		east;
	t_img		west;
}				t_game;

void	ray_caster(t_game *game);

float	deg_to_rad(float angle);
float	fix_angle(float angle);

t_line	init_line(int x1, int y1, int x2, int y2);
void	draw_line(t_img *img, t_line *l, int color);
void	draw_rect(t_img *img, int x, int y, int w, int h, int color);
void	apply_texture(t_game *g, t_ray *ray, t_wall* wall);
void	load_texture(char *path, t_img *texture, t_game *g);
int		rgb_to_int(uint8_t *colors_input);
void	put_pixel(t_img *img, int x, int y, int color);

#endif
