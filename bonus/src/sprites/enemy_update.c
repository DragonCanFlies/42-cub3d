/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:45:01 by latabagl          #+#    #+#             */
/*   Updated: 2026/03/31 12:58:19 by latabagl         ###   ########.fr       */
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

/*
** Computes the time elapsed since the last frame in seconds (delta_time),
** by retrieving the current time and subtracting the last frame's time.
** Clamps delta_time within one second to prevent extreme values that
** could occur if the game freezes or lags.
*/
void	update_delta_time(t_game *g)
{
	static struct timeval	last_tv;
	static int				initialized;
	struct timeval			current_tv;
	float					delta_sec;
	float					delta_usec;

	gettimeofday(&current_tv, NULL);
	if (!initialized)
	{
		last_tv = current_tv;
		initialized = 1;
		g->delta_time = 0.0f;
		return ;
	}
	delta_sec = (float)(current_tv.tv_sec - last_tv.tv_sec);
	delta_usec = (float)(current_tv.tv_usec - last_tv.tv_usec) / 1000000.0f;
	g->delta_time = delta_sec + delta_usec;
	if (g->delta_time > 1.0f)
		g->delta_time = 1.0f;
	if (g->delta_time < 0.0f)
		g->delta_time = 0.0f;
	last_tv = current_tv;
}
