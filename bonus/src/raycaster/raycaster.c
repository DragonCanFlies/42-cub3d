/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:02:19 by latabagl          #+#    #+#             */
/*   Updated: 2026/04/05 14:05:23 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Applies fish eye correction to the wall distance
*/
static void	apply_fisheye_correction(t_game *g, t_wall *w, t_ray *r)
{
	w->ca = (int)fix_angle(g->player.angle - r->ra);
	w->dis *= cos(deg_to_rad(w->ca));
}

/*
** computes the height of the wall slice based on the corrected distance
** and applies the wall texture
*/
static void	draw_wall(t_game *g, t_wall *w, t_ray *r)
{
	w->line_h = (MAP_S * WIN_HEIGHT) / w->dis;
	if (w->line_h < 1)
		w->line_h = 1;
	apply_texture(g, r, w);
}

/*
** Compares distance of vertical and horizontal wall hits,
** selects the closest intersection
** and stores the wall hit position and distance from the player
*/
static void	compare_distance(t_ray *ray, t_wall *wall)
{
	if (ray->dis_v < ray->dis_h)
	{
		wall->x = ray->v_hit_x;
		wall->y = ray->v_hit_y;
		wall->dis = ray->dis_v;
	}
	else
	{
		wall->x = ray->h_hit_x;
		wall->y = ray->h_hit_y;
		wall->dis = ray->dis_h;
	}
}

/*
** Stores the wall distance in the z-buffer for each screen x coordinate
** covered by the current ray
*/
static void	fill_zbuffer(t_game *game, t_ray *ray, float dist)
{
	int	x;
	int	x_end;

	x = (int)(ray->index * game->px_per_ray);
	x_end = (int)((ray->index + 1) * game->px_per_ray);
	if (x_end > WIN_WIDTH)
		x_end = WIN_WIDTH;
	while (x < x_end)
	{
		if (x >= 0 && x < WIN_WIDTH)
			game->zbuffer[x] = dist;
		x++;
	}
}

/*
** Raycasting:
** casts rays across the player's field of view.
** For each ray uses the DDA algorithm to find the closest wall hit,
** and renders the corresponding wall slice
*/
void	ray_caster(t_game *game)
{
	t_ray	ray;
	t_wall	wall;
	float	angle_offset;

	ray.index = 0;
	ray.ra = fix_angle(game->player.angle + (FOV / 2));
	angle_offset = 0;
	while (angle_offset < FOV)
	{
		check_vertical(&ray, game);
		check_horizontal(&ray, game);
		compare_distance(&ray, &wall);
		apply_fisheye_correction(game, &wall, &ray);
		fill_zbuffer(game, &ray, wall.dis);
		draw_wall(game, &wall, &ray);
		ray.ra = fix_angle(ray.ra - RAY_ACC);
		angle_offset += RAY_ACC;
		ray.index++;
	}
}
