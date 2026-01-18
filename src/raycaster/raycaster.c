#include "cub3d.h"

static void	draw_wall(t_game *g, t_wall *w, t_ray *r)
{
	// int		i;
	// int		x;
	// int		y;
	// int		x1;
	// t_line	line;

	w->ca = (int)fix_angle(g->player.angle - r->ra);
	w->dis *= cos(deg_to_rad(w->ca));//fisheye correction
	w->line_h = (MAP_S * WIN_HEIGHT) / w->dis;
	// g->zbuffer[(int)(r->index * g->px_per_ray)] = w->dis;
	apply_texture(g, r, w);
	// if (w->line_h > WIN_HEIGHT)
	// 	w->line_h = WIN_HEIGHT;
	// w->line_offset = (WIN_HEIGHT >> 1) - (w->line_h >> 1);
	// i = 0;
	// x = (int)r->index * g->px_per_ray;
	// y = w->line_offset;
	// x1 = (int)((r->index + 1) * g->px_per_ray) - 1;
	// while (i < w->line_h)
	// {
	// 	line = init_line(x, y + i, x1, y + i);
	// 	draw_line(&g->img, &line, w->color);
	// 	i++;
	// }
}

static void	compare_distance(t_ray *ray, t_wall *wall)
{
	if (ray->dis_v < ray->dis_h)
	{
		wall->x = ray->v_hit_x;
		wall->y = ray->v_hit_y;
		wall->dis = ray->dis_v;
		wall->color = 0x009900;
	}
	else
	{
		wall->x = ray->h_hit_x;
		wall->y = ray->h_hit_y;
		wall->dis = ray->dis_h;
		wall->color = 0x00CC00;
	}
}
static void fill_zbuffer(t_game *game, t_ray *ray, float dist)
{
    int x = (int)(ray->index * game->px_per_ray);
    int x_end = (int)((ray->index + 1) * game->px_per_ray);
    
    if (x_end > WIN_WIDTH)
        x_end = WIN_WIDTH;
    while (x < x_end)
    {
        if (x >= 0 && x < WIN_WIDTH)
            game->zbuffer[x] = dist;
        x++;
    }
}

void	ray_caster(t_game *game)
{
	t_ray	ray;
	t_wall	wall;
	float	angle_offset;

	ray.index = 0;
	ray.ra = fix_angle(game->player.angle + (FOV / 2));
	angle_offset = 0;
	while (angle_offset < FOV - RAY_ACC)//debug added ray_acc
	{
		check_vertical(&ray, game);
		check_horizontal(&ray, game);
		compare_distance(&ray, &wall);
		fill_zbuffer(game, &ray, wall.dis);
		draw_wall(game, &wall, &ray);
		ray.ra = fix_angle(ray.ra - RAY_ACC);
		angle_offset += RAY_ACC;
		ray.index++;
	}
}
