/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_shoot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:51:31 by latabagl          #+#    #+#             */
/*   Updated: 2026/04/05 17:14:53 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Returns the distance between two points
*/
static float	calc_dist(float x1, float y1, float x2, float y2)
{
	float	dx;
	float	dy;

	dx = x2 - x1;
	dy = y2 - y1;
	return (sqrtf(dx * dx + dy * dy));
}

/*
** Returns the dot product between the player's view direction
** and the direction from the player to the sprite.
** Used to determine if the sprite is inside the player's aim cone.
*/
static float	calc_aim_dot(t_game *g, t_sprite *s, float dist)
{
	float	to_x;
	float	to_y;

	to_x = (s->x - g->player.x) / dist;
	to_y = (s->y - g->player.y) / dist;
	return (g->player.dx * to_x + g->player.dy * to_y);
}

/*
** Finds the closest alive enemy sprite that is inside
** the player's aim cone
*/
static t_sprite	*find_target(t_game *g)
{
	int			i;
	float		dist;
	float		dot;
	t_sprite	*closest;
	float		min_dist;

	i = 0;
	closest = NULL;
	min_dist = 999999.0f;
	while (i < g->sprite_count)
	{
		if (g->sprites[i].type == TYPE_ENEMY && g->sprites[i].alive)
		{
			dist = calc_dist(g->player.x, g->player.y,
					g->sprites[i].x, g->sprites[i].y);
			dot = calc_aim_dot(g, &g->sprites[i], dist);
			if (dot > 0.9f && dist < min_dist)
			{
				min_dist = dist;
				closest = &g->sprites[i];
			}
		}
		i++;
	}
	return (closest);
}

/*
** Handles player shooting:
** - checks weapon state, fire cooldown and ammo
** - fires the shot
** - starts firing animation if needed
** - finds and damages the target
*/
void	player_shoot(t_game *g)
{
	t_sprite	*target;

	if (!g->gun.active)
		return ;
	if (g->gun.fire_cooldown > 0.0f)
		return ;
	if (g->gun.ammo <= 0)
		return ;
	g->gun.ammo--;
	g->gun.fire_cooldown = FIRE_RATE;
	if (g->gun.state == GUN_IDLE || g->gun.state == GUN_FIRE_END)
	{
		g->gun.state = GUN_FIRE_START;
		g->gun.anim_timer = 0.0f;
	}
	target = find_target(g);
	if (target)
	{
		target->health--;
		if (target->health <= 0)
		{
			target->alive = 0;
			ft_putstr_fd("Enemy killed!\n", 1);
		}
	}
}
