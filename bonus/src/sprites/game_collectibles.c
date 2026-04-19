/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_collectibles.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:49:28 by latabagl          #+#    #+#             */
/*   Updated: 2026/03/31 13:43:55 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	calc_dist_to_player(t_game *g, t_sprite *s)
{
	float	dx;
	float	dy;

	dx = g->player.x - s->x;
	dy = g->player.y - s->y;
	return (sqrtf(dx * dx + dy * dy));
}

// Reset g->gun.timer to 10 seconds
static void	collect_fruit(t_game *g)
{
	g->gun.ammo += AMMO_PER_FRUIT;
	g->gun.timer = GUN_DURATION;
	g->gun.active = 1;
	ft_putstr_fd("Weapon acquired! +100 AMMO! Press SPACE to shoot!\n", 1);
	g->health += 20;
	if (g->health > g->max_health)
		g->health = g->max_health;
	ft_putstr_fd("Food collected! +20 HP!\n", 1);
}

static void	collect_food(t_game *g)
{
	g->collectibles--;
	if (g->collectibles == 0)
		ft_putstr_fd("All food collected! Find the exit!\n", 1);
}

static void	collect_item(t_game *g, t_sprite *s)
{
	if (s->type == TYPE_FRUIT)
		collect_fruit(g);
	else if (s->type == TYPE_FOOD)
		collect_food(g);
	s->alive = 0;
}

void	check_collectibles(t_game *g)
{
	int		i;
	float	dist;

	i = 0;
	while (i < g->sprite_count)
	{
		if (g->sprites[i].alive && g->sprites[i].type != TYPE_ENEMY)
		{
			dist = calc_dist_to_player(g, &g->sprites[i]);
			if (dist < 32.0f)
				collect_item(g, &g->sprites[i]);
		}
		i++;
	}
}
