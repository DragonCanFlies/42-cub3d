#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# define WIN_WIDTH	1024
# define WIN_HEIGHT	510
# define MAP_X		8
# define MAP_Y		8
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
	int		dof;        // Depth of field
	int		mx;         // Map X coordinate
	int		my;         // Map Y coordinate
	int		mp;         // Map position (array index)
}			t_ray;

typedef struct s_wall
{
	int	line_h;     // Wall height
	int	line_offset;   // Wall offset
	int	ca;         // Corrected angle
	int	color;      // Wall color
	float	x;
	float	y;
	float	dis;
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

typedef struct s_img
{
	void	*img;
	char	*buffer;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

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
	int			map[MAP_X * MAP_Y];
	int			px_per_ray;
}				t_game;


void	ray_caster(t_game *game);

float	deg_to_rad(float angle);
float	fix_angle(float angle);

#endif
