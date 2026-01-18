/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:00:00 by loasaad           #+#    #+#             */
/*   Updated: 2026/01/16 16:26:01 by loasaad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_sprites(t_game *g)
{
	update_enemies(g);
	check_collectibles(g);
}

static int	is_enemy(t_sprite *s)
{
	return (s->type == TYPE_ENEMY && s->alive);
}

void	update_enemies(t_game *g)
{
	int	i;

	i = 0;
	while (i < g->sprite_count)
	{
		if (is_enemy(&g->sprites[i]))
		{
			move_enemy(g, &g->sprites[i]);
			animate_enemy(g, &g->sprites[i]);
		}
		i++;
	}
}

static float	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0f);
}

void	update_delta_time(t_game *g)
{
	float	current_time;

	current_time = get_time();
	g->delta_time = current_time - g->last_time;
	g->last_time = current_time;
}