#include "cub3d.h"

static void	get_wall_orientation(t_game *g, t_ray *ray, t_wall* wall)
{
	if (ray->dis_v < ray->dis_h)
	{
		// vertical wall facing west
		wall->text = g->tex.west;
		wall->wall_dir = W;
		if (cos(deg_to_rad(ray->ra)) < -0.001)
		{
			// vertical wall facing east
			wall->text = g->tex.east;
			wall->wall_dir = E;
		}
	}
	else
	{
		// horizontal wall facing south
		wall->text = g->tex.south;
		wall->wall_dir = S;
		if (sin(deg_to_rad(ray->ra)) < -0.001)
		{
			// horizontal wall facing north
			wall->text = g->tex.north;
			wall->wall_dir = N;
		}
	}
	wall->text_h = wall->text.height;
}

static void	compute_tx(t_ray *ray, t_wall* wall)
{
	if (wall->wall_dir == W)
		wall->tx = ((int) ray->v_hit_y % MAP_S) / (MAP_S / wall->text_h);
	else if (wall->wall_dir == E)
	{
		wall->tx = ((int) ray->v_hit_y % MAP_S) / (MAP_S / wall->text_h);
		wall->tx = wall->text_h - 1 - wall->tx;
	}
	else if (wall->wall_dir == S)
		wall->tx = ((int) ray->h_hit_x % MAP_S) / (MAP_S / wall->text_h);
	else if (wall->wall_dir == N)
	{
		wall->tx = ((int) ray->h_hit_x % MAP_S) / (MAP_S / wall->text_h);
		wall->tx = wall->text_h - 1 - wall->tx;
	}
}

static void	compute_ty(t_wall* wall)
{
	wall->ty_off = 0;
	wall->ty_step = (float)wall->text_h / (float)wall->line_h;
	if (wall->line_h > WIN_HEIGHT)
	{
		wall->ty_off = (wall->line_h - WIN_HEIGHT) >> 1;
		wall->line_h = WIN_HEIGHT;
	}
	wall->ty = wall->ty_step * wall->ty_off;
	wall->line_offset = WIN_HEIGHT / 2 - (wall->line_h >> 1);
}

static void	check_boundaries(t_wall* wall)
{
	if (wall->tx < 0)
		wall->tx = 0;
	if (wall->tx >= wall->text_h)
		wall->tx = wall->text_h - 1;
	if (wall->ty < 0)
		wall->ty = 0;
	if (wall->ty >= wall->text_h)
		wall->ty = wall->text_h - 1;
}

static void	draw_wall(t_game *g, t_ray *ray, t_wall* wall)
{
	int		ray_width;
	int		i;
	int		color;
	t_line	line;

	ray_width = (WIN_WIDTH * RAY_ACC) / FOV;
	i = 0;
	while (i < wall->line_h)
	{
		// TODO change with size of texture - 1
		color = *(unsigned int *)(wall->text.buffer + ((int)wall->ty & 63) * wall->text.line_len + ((int)wall->tx & 63) * (wall->text.bpp >> 3));
		line = init_line(ray->index * ray_width, wall->line_offset + i, ray->index * ray_width + ray_width - 1, wall->line_offset + i);
		draw_line(&g->img, &line, color);
		wall->ty += wall->ty_step;
		i++;
	}
}

/*In main :

t_ray	ray;
And fill these:
	int		shade; // horizontal 0 vs vertical 1 wall
	float	ra; // ray angle
	float	rx; // coordinates of ray on wall
	float	ry;
	int		line_h; // height of section to draw on screen
*/
void	apply_texture(t_game *g, t_ray *ray, t_wall* wall)
{
	get_wall_orientation(g, ray, wall);
	compute_tx(ray, wall);
	compute_ty(wall);
	check_boundaries(wall);
	draw_wall(g, ray, wall);
}

