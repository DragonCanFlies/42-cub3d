/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:50:13 by latabagl          #+#    #+#             */
/*   Updated: 2026/04/05 17:36:08 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Computes the angle between the player and the sprite
*/
static float	calc_sprite_angle(t_game *g, float rel_x,
	float rel_y, float p_angle)
{
	float	angle_to_spr;
	float	angle_diff;

	angle_to_spr = atan2f(-rel_y, rel_x) * g->rad_to_deg;
	angle_diff = angle_to_spr - p_angle;
	while (angle_diff > 180.0f)
		angle_diff -= 360.0f;
	while (angle_diff < -180.0f)
		angle_diff += 360.0f;
	return (angle_diff);
}

/*
** Applies fish eye correction to the distance of the sprite
*/
static float	calc_perp_dist(float dist, float angle_from_center)
{
	float	perp_dist;

	perp_dist = dist * cosf(deg_to_rad(angle_from_center));
	if (perp_dist > 0 && perp_dist < MIN_SPRITE_DIST)
		perp_dist = MIN_SPRITE_DIST;
	return (perp_dist);
}

static void	calc_transform(t_game *g, t_sprite *s, t_spr_draw *d)
{
	float	rel_x;
	float	rel_y;
	float	dist;
	float	angle_diff;
	float	ray_offset;

	rel_x = s->x - g->player.x;
	rel_y = s->y - g->player.y;
	dist = sqrtf(rel_x * rel_x + rel_y * rel_y);
	angle_diff = calc_sprite_angle(g, rel_x, rel_y, g->player.angle);
	ray_offset = g->half_fov - angle_diff;
	d->ray_x = ray_offset * g->inv_ray_acc;
	d->dist_y = calc_perp_dist(dist, angle_diff);
}

static void	calc_screen_pos(t_game *g, t_spr_draw *d)
{
	int	size;

	d->scr_x = (int)(d->ray_x * g->px_per_ray);
	size = abs((int)(MAP_S * WIN_HEIGHT / d->dist_y));
	if (size > g->max_sprite_size)
		size = g->max_sprite_size;
	d->height = size;
	d->width = size;
}

void	transform_sprite(t_game *g, t_sprite *s, t_spr_draw *d)
{
	calc_transform(g, s, d);
	calc_screen_pos(g, d);
}
