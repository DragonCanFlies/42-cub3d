/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:43:17 by latabagl          #+#    #+#             */
/*   Updated: 2026/03/31 13:45:05 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	normalize_direction(float *dx, float *dy, float dist)
{
	if (dist > 0.1f)
	{
		*dx /= dist;
		*dy /= dist;
	}
}

static int	can_move_enemy(t_game *g, float x, float y)
{
	int	mx;
	int	my;
	int	mp;

	mx = (int)x >> 6;
	my = (int)y >> 6;
	mp = my * g->map.x + mx;
	if (mp < 0 || mp >= g->map.x * g->map.y)
		return (0);
	return (g->map.map_data[mp] == 0);
}

static void	apply_movement(t_game *g, t_sprite *e, float dx, float dy)
{
	float	new_x;
	float	new_y;

	new_x = e->x + dx * ENEMY_SPEED;
	new_y = e->y + dy * ENEMY_SPEED;
	if (can_move_enemy(g, new_x, e->y))
		e->x = new_x;
	if (can_move_enemy(g, e->x, new_y))
		e->y = new_y;
}

static void	take_damage(t_game *g)
{
	g->health -= ENEMY_DAMAGE;
	g->damage_cooldown = DAMAGE_COOLDOWN;
	if (g->health <= 0)
	{
		g->health = 0;
		ft_putstr_fd("Game Over! You died!\n", 1);
		close_window(g);
	}
	else
	{
		ft_putstr_fd("Hit by enemy! -20 HP\n", 1);
	}
}

void	move_enemy(t_game *g, t_sprite *e)
{
	float	dx;
	float	dy;
	float	dist;

	dx = g->player.x - e->x;
	dy = g->player.y - e->y;
	dist = calc_dist_to_player(g, e);
	if (dist < 32.0f)
	{
		if (g->damage_cooldown <= 0.0f)
			take_damage(g);
	}
	normalize_direction(&dx, &dy, dist);
	apply_movement(g, e, dx, dy);
}
