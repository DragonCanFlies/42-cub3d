/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:06:51 by latabagl          #+#    #+#             */
/*   Updated: 2026/04/01 18:28:47 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_minimap_cell(t_img *img, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_S)
	{
		j = 0;
		while (j < MINIMAP_S)
		{
			put_pixel(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

static void	draw_minimap_player(t_game *g, int start_x)
{
	int	i;
	int	j;
	int	px;
	int	py;

	px = (int)(g->player.x / MINIMAP_S);
	py = (int)(g->player.y / MINIMAP_S);
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			put_pixel(&g->img, start_x + px + j, py + i, 0x00ff00);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_game *g)
{
	int	x;
	int	y;
	int	color;
	int	start_x;

	start_x = WIN_WIDTH - g->map.x * MINIMAP_S;
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
			draw_minimap_cell(&g->img, start_x + (x * MINIMAP_S),
				y * MINIMAP_S, color);
			x++;
		}
		y++;
	}
	draw_minimap_player(g, start_x);
}
