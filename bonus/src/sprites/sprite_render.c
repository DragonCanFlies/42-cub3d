/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:49:54 by latabagl          #+#    #+#             */
/*   Updated: 2026/02/03 18:49:55 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_sprites(t_game *g)
{
	int	i;

	calc_spr_dist(g);
	sort_sprites(g);
	i = 0;
	while (i < g->sprite_count)
	{
		if (g->sprites[i].alive)
			draw_sprite(g, &g->sprites[i]);
		i++;
	}
}
