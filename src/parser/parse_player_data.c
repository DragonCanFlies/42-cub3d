/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:01:13 by latabagl          #+#    #+#             */
/*   Updated: 2026/03/22 17:11:22 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Returns 1 if the character represents a player starting orientation
static int	is_orientation(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/*
** Initializes the player starting position (in-game coordinates),
** sets the initial angle based on orientation (N/S/E/W),
** computes the initial movement direction vector (dx, dy)
** and replaces the starting position with '0' in the map
*/
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

/*
** Finds the player starting tile and initializes player data
*/
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
