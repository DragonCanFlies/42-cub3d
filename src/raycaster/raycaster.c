/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:02:19 by latabagl          #+#    #+#             */
/*   Updated: 2026/04/05 14:04:13 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Applies fish eye correction to the wall distance,
** computes the height of the wall slice based on the corrected distance
** and applies the wall texture
*/
static void	draw_wall(t_game *g, t_wall *w, t_ray *r)
{
	w->ca = (int)fix_angle(g->player.angle - r->ra);
	w->dis *= cos(deg_to_rad(w->ca));
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
		draw_wall(game, &wall, &ray);
		ray.ra = fix_angle(ray.ra - RAY_ACC);
		angle_offset += RAY_ACC;
		ray.index++;
	}
}
