/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_distance.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:46:58 by latabagl          #+#    #+#             */
/*   Updated: 2026/03/31 15:45:12 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Computes and stores the distance between each alive sprite and the player.
*/
void	calc_spr_dist(t_game *g)
{
	int		i;
	float	dx;
	float	dy;

	i = 0;
	while (i < g->sprite_count)
	{
		if (g->sprites[i].alive)
		{
			dx = g->sprites[i].x - g->player.x;
			dy = g->sprites[i].y - g->player.y;
			g->sprites[i].dist = sqrtf(dx * dx + dy * dy);
		}
		i++;
	}
}

/*
** Swaps two sprites in memory.
*/
static void	swap_sprites(t_sprite *a, t_sprite *b)
{
	t_sprite	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
** Sorts sprites from farthest to nearest using bubble sort.
** Ensures that distant sprites are drawn first and closer sprites
** are rendered on top of them.
*/
void	sort_sprites(t_game *g)
{
	int	i;
	int	j;

	i = 0;
	while (i < g->sprite_count - 1)
	{
		j = 0;
		while (j < g->sprite_count - i - 1)
		{
			if (g->sprites[j].dist < g->sprites[j + 1].dist)
				swap_sprites(&g->sprites[j], &g->sprites[j + 1]);
			j++;
		}
		i++;
	}
}
