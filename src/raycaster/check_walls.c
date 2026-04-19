/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:02:04 by latabagl          #+#    #+#             */
/*   Updated: 2026/04/05 19:00:22 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Based on the ray direction (up, down or left/right),
** computes the coordinates of the first horizontal grid intersection,
** and the offsets used to step through the grid
*/
static void	check_direction_h(t_ray *ray, t_game *g)
{
	if (sin(deg_to_rad(ray->ra)) > 0.001)
	{
		ray->ry = (((int)g->player.y / MAP_S) * MAP_S) - 0.0001;
		ray->rx = (g->player.y - ray->ry) * ray->tan_val + g->player.x;
		ray->yo = -64;
		ray->xo = -ray->yo * ray->tan_val;
	}
	else if (sin(deg_to_rad(ray->ra)) < -0.001)
	{
		ray->ry = (((int)g->player.y / MAP_S) * MAP_S) + 64;
		ray->rx = (g->player.y - ray->ry) * ray->tan_val + g->player.x;
		ray->yo = 64;
		ray->xo = -ray->yo * ray->tan_val;
	}
	else
	{
		ray->rx = g->player.x;
		ray->ry = g->player.y;
		ray->dof = g->map.y;
	}
}

/*
** Based on the ray direction (right, left or up/down),
** computes the coordinates of the first vertical grid intersection,
** and the offsets used to step through the grid
*/
static void	check_direction_v(t_ray *ray, t_game *g)
{
	if (cos(deg_to_rad(ray->ra)) > 0.001)
	{
		ray->rx = (((int)g->player.x / MAP_S) * MAP_S) + MAP_S;
		ray->ry = (g->player.x - ray->rx) * ray->tan_val + g->player.y;
		ray->xo = MAP_S;
		ray->yo = -ray->xo * ray->tan_val;
	}
	else if (cos(deg_to_rad(ray->ra)) < -0.001)
	{
		ray->rx = (((int)g->player.x / MAP_S) * MAP_S) - 0.0001;
		ray->ry = (g->player.x - ray->rx) * ray->tan_val + g->player.y;
		ray->xo = -MAP_S;
		ray->yo = -ray->xo * ray->tan_val;
	}
	else
	{
		ray->rx = g->player.x;
		ray->ry = g->player.y;
		ray->dof = g->map.x;
	}
}

/*
** Checks vertical intersections to find a wall hit
*/
void	check_vertical(t_ray *ray, t_game *g)
{
	ray->dof = 0;
	ray->dis_v = 100000;
	ray->tan_val = tan(deg_to_rad(ray->ra));
	check_direction_v(ray, g);
	while (ray->dof < g->map.x)
	{
		ray->mx = (int)(ray->rx) / MAP_S;
		ray->my = (int)(ray->ry) / MAP_S;
		ray->mp = ray->my * g->map.x + ray->mx;
		if (ray->mp >= 0 && ray->mp < g->map.x * g->map.y
			&& g->map.map_data[ray->mp] == 1)
		{
			ray->dof = g->map.x;
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

/*
** Checks horizontal intersections to find a wall hit
*/
void	check_horizontal(t_ray *ray, t_game *g)
{
	ray->dof = 0;
	ray->dis_h = 100000;
	ray->tan_val = 1.0 / ray->tan_val;
	check_direction_h(ray, g);
	while (ray->dof < g->map.y)
	{
		ray->mx = (int)(ray->rx) / MAP_S;
		ray->my = (int)(ray->ry) / MAP_S;
		ray->mp = ray->my * g->map.x + ray->mx;
		if (ray->mp >= 0 && ray->mp < g->map.x * g->map.y
			&& g->map.map_data[ray->mp] == 1)
		{
			ray->dof = g->map.y;
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
