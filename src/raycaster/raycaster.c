#include "cub3d.h"

// static void	draw_wall(t_game *g, t_wall *w, float ra, int r)
// {
// 	int		i;
// 	int		x;
// 	int		y;
// 	int		x1;
// 	t_line	line;

// 	w->ca = (int)fix_angle(g->player.angle - ra);
// 	w->dis *= cos(deg_to_rad(w->ca));//fisheye correction
// 	w->line_h = (MAP_S * WIN_HEIGHT) / w->dis;
// 	if (w->line_h > WIN_HEIGHT)
// 		w->line_h = WIN_HEIGHT;
// 	w->line_offset = (WIN_HEIGHT / 2) - (w->line_h >> 1);
// 	i = 0;
// 	x = r * g->px_per_ray;
// 	y = w->line_offset;
// 	x1 = x + g->px_per_ray - 1;
// 	while (i < w->line_h)
// 	{
// 		line = init_line(x, y + i, x1, y + i);
// 		draw_line(&g->img, &line, w->color);
// 		i++;
// 	}
// }

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

void	ray_caster(t_game *game)
{
	t_ray	ray;
	t_wall	wall;

	ray.ra = fix_angle(game->player.angle + (FOV / 2));
	ray.r = 0;
	while (ray.r < FOV)
	{
		check_vertical(&ray, game);
		check_horizontal(&ray, game);
		compare_distance(&ray, &wall);
		// draw_wall(game, &wall, ray.ra, ray.r);
		wall.ca = (int)fix_angle(game->player.angle - ray.ra);
		wall.dis *= cos(deg_to_rad(wall.ca));//fisheye correction
		wall.line_h = (MAP_S * WIN_HEIGHT) / wall.dis;
		apply_texture(game, &ray, &wall);
		ray.ra = fix_angle(ray.ra - RAY_ACC);
		ray.r += RAY_ACC;
	}
}
