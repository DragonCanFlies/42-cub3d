#include "cub3d.h"

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
void	check_vertical(t_ray *ray, t_game *g)
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

void	check_horizontal(t_ray *ray, t_game *g)
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