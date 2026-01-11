#include "cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	unsigned int	*dst;
	int				buffer_placement;
	
	if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
		return;
	buffer_placement = (y * img->line_len) + (x * (img->bpp / 8));
	dst = (unsigned int *)(img->buffer + buffer_placement);
	*dst = color;
}

void	draw_rect(t_img *img, int x, int y, int w, int h, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			put_pixel(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_line(t_img *img, t_line *l, int color)
{
	int e2;

	while (1)
	{
		put_pixel(img, l->x1, l->y1, color);
		if (l->x1 == l->x2 && l->y1 == l->y2)
			break;
		e2 = 2 * l->err;
		if (e2 > -l->dy)
		{
			l->err -= l->dy;
			l->x1 += l->sx;
		}
		if (e2 < l->dx)
		{
			l->err += l->dx;
			l->y1 += l->sy;
		}
	}
}
t_line	init_line(int x1, int y1, int x2, int y2)
{
	t_line	line;

	line.x1 = x1;
	line.x2 = x2;
	line.y1 = y1;
	line.y2	= y2;
	line.dx = abs(x2 - x1);
	line.dy = abs(y2 - y1);
	if (x1 < x2)
		line.sx = 1;
	else
		line.sx = -1;
	if (y1 < y2)
		line.sy = 1;
	else
		line.sy = -1;
	line.err = line.dx - line.dy;
	return (line);
}
static void	check_direction_h(t_ray *ray, t_game *g)
{
	if (sin(deg_to_rad(ray->ra)) > 0.001)//looking up
	{
		ray->ry = (((int)g->player.y >> 6) << 6) - 0.0001;
		ray->rx = (g->player.y - ray->ry) * ray->tan_val + g->player.x;
		ray->yo = -64;
		ray->xo = -ray->yo * ray->tan_val;
	}
	else if (sin(deg_to_rad(ray->ra)) < -0.001)//looking down
	{
		ray->ry = (((int)g->player.y >> 6) << 6) + 64;
		ray->rx = (g->player.y - ray->ry) * ray->tan_val + g->player.x;
		ray->yo = 64;
		ray->xo = -ray->yo * ray->tan_val;
	}
	else
	{
		ray->rx = g->player.x;
		ray->ry = g->player.y;
		ray->dof = MAP_Y;
	}
}

static void	check_direction_v(t_ray *ray, t_game *g)
{
	if (cos(deg_to_rad(ray->ra)) > 0.001)//looking right
	{
		ray->rx = (((int)g->player.x >> 6) << 6) + 64;
		ray->ry = (g->player.x - ray->rx) * ray->tan_val + g->player.y;
		ray->xo = 64;
		ray->yo = -ray->xo * ray->tan_val;
	}
	else if (cos(deg_to_rad(ray->ra)) < -0.001)//looking left
	{
		ray->rx = (((int)g->player.x >> 6) << 6) + - 0.0001;
		ray->ry = (g->player.x - ray->rx) * ray->tan_val + g->player.y;
		ray->xo = -64;
		ray->yo = -ray->xo * ray->tan_val;
	}
	else
	{
		ray->rx = g->player.x;
		ray->ry = g->player.y;
		ray->dof = MAP_X;
	}
}
static void	check_vertical(t_ray *ray, t_game *g)
{
	ray->dof = 0;
	ray->dis_v = 100000;
	ray->tan_val = tan(deg_to_rad(ray->ra));
	check_direction_v(ray, g);
	while (ray->dof < MAP_X)
	{
		ray->mx = (int)(ray->rx) >> 6;
		ray->my = (int)(ray->ry) >> 6;
		ray->mp = ray->my * MAP_X + ray->mx;
		if (ray->mp >= 0 && ray->mp < MAP_X * MAP_Y && g->map[ray->mp] == 1)
		{
			ray->dof = MAP_X;
			ray->dis_v = cos(deg_to_rad(ray->ra)) * (ray->rx - g->player.x)
			- sin(deg_to_rad(ray->ra)) * (ray->ry - g->player.y);
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->dof++;
		}
	}
	ray->v_hit_x = ray->rx;
	ray->v_hit_y = ray->ry;
}

static void	check_horizontal(t_ray *ray, t_game *g)
{
	ray->dof = 0;
	ray->dis_h = 100000;
	ray->tan_val = 1.0 / ray->tan_val;
	check_direction_h(ray, g);
	while (ray->dof < MAP_Y)
	{
		ray->mx = (int)(ray->rx) >> 6;
		ray->my = (int)(ray->ry) >> 6;
		ray->mp = ray->my * MAP_X + ray->mx;
		if (ray->mp >= 0 && ray->mp < MAP_X * MAP_Y && g->map[ray->mp] == 1)
		{
			ray->dof = MAP_Y;
			ray->dis_h = cos(deg_to_rad(ray->ra)) * (ray->rx - g->player.x)
			- sin(deg_to_rad(ray->ra)) * (ray->ry - g->player.y);
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->dof++;
		}
	}
	ray->h_hit_x = ray->rx;
	ray->h_hit_y = ray->ry;
}

void	draw_wall(t_game *g, t_wall *w, float ra, int r)
{
	int		i;
	int		x;
	int		y;
	int		x1;
	t_line	line;

	w->ca = (int)fix_angle(g->player.angle - ra);
	w->dis *= cos(deg_to_rad(w->ca));//fisheye correction
	w->line_h = (MAP_S * WIN_HEIGHT) / w->dis;
	if (w->line_h > WIN_HEIGHT)
		w->line_h = WIN_HEIGHT;
	w->line_offset = (WIN_HEIGHT / 2) - (w->line_h >> 1);
	i = 0;
	x = r * g->px_per_ray;
	y = w->line_offset;
	x1 = x + g->px_per_ray - 1;
	while (i < w->line_h)
	{
		line = init_line(x, y + i, x1, y + i);
		draw_line(&g->img, &line, w->color);
		i++;
	}
}

void	ray_caster(t_game *game)
{
	t_ray	ray;
	t_wall	wall;
	int		r;

	ray.ra = fix_angle(game->player.angle + (FOV / 2));
	r = 0;
	while (r < FOV)
	{
		check_vertical(&ray, game);
		check_horizontal(&ray, game);
		if (ray.dis_v < ray.dis_h)
		{
			wall.x = ray.v_hit_x;
			wall.y = ray.v_hit_y;
			wall.dis = ray.dis_v;
			wall.color = 0x009900;
		}
		else
		{
			wall.x = ray.h_hit_x;
			wall.y = ray.h_hit_y;
			wall.dis = ray.dis_h;
			wall.color = 0x00CC00;
		}
		draw_wall(game, &wall, ray.ra, r);
		ray.ra = fix_angle(ray.ra - RAY_ACC);
		r += RAY_ACC;
	}
}
