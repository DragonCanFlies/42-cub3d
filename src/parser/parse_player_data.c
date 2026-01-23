/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:01:13 by latabagl          #+#    #+#             */
/*   Updated: 2026/01/22 18:01:20 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_orientation(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	init_player(t_game *g, int row, int col)
{
	g->player.x = col * MAP_S + (MAP_S / 2);
	g->player.y = row * MAP_S + (MAP_S / 2);
	if (g->map.raw_map[row][col] == 'N')
		g->player.angle = 90.0;
	else if (g->map.raw_map[row][col] == 'S')
		g->player.angle = 270.0;
	else if (g->map.raw_map[row][col] == 'W')
		g->player.angle = 180.0;
	else
		g->player.angle = 0.0;
	g->map.raw_map[row][col] = '0';
	g->player.dx = cos(deg_to_rad(g->player.angle));
	g->player.dy = -sin(deg_to_rad(g->player.angle));
}

void	parse_player_data(t_game *g)
{
	int	row;
	int	col;

	row = 0;
	while (g->map.raw_map[row])
	{
		col = 0;
		while (g->map.raw_map[row][col])
		{
			if (is_orientation(g->map.raw_map[row][col]))
			{
				init_player(g, row, col);
				return ;
			}
			col++;
		}
		row++;
	}
	return ;
}
