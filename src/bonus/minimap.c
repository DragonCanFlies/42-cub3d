/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:06:51 by latabagl          #+#    #+#             */
/*   Updated: 2026/01/21 22:46:56 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap(t_game *g)
{
	int	x;
	int	y;
	int	color;

	int	px;
	int py;

	px = (int)(g->player.x / 8);
	py = (int)(g->player.y / 8);

	draw_rect(&g->img, 0, 0, g->map.x * 8, g->map.y * 8, 0x000000);
	y = 0;
	while (y < g->map.y)
	{
		x = 0;
		while (x < g->map.x)
		{
			if (g->map.map_data[y * g->map.x + x] == 1)
				color = 0xffffff;
			else
				color = 0x000000;
			draw_rect(&g->img, 0 + (x * 8), 0 + (y * 8), 7, 7, color);
			x++;
		}
		y++;
	}
	draw_rect(&g->img, px, py, 4, 4, 0x00ff00);
	return ;
}
