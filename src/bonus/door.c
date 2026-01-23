/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:23:54 by latabagl          #+#    #+#             */
/*   Updated: 2026/01/21 16:39:33 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_door_at(t_game *g, int x, int y)
{
	int	i;
	int	p;

	p = y * g->map.x + x;
	if (p < 0 || (p >= g->map.x * g->map.y))
		return (0);
	i = 0;
	while (i < g->map.doors_nb)
	{
		if ((x == g->map.doors[i].x)
			&& (y == g->map.doors[i].y)
			&& g->map.doors[i].open == 0)
		{
			g->map.doors[i].open = 1;
			g->map.map_data[p] = 0;
			return (1);
		}
		i++;
	}
	return (0);
}

// opened door is replaced with walking tile
void	open_door(t_game *g)
{
	int	distance;
	int	check_x;
	int	check_y;

	distance = PLAYER_RADIUS;
	while (distance < MAP_S)
	{
		check_x = (int)((g->player.x + g->player.dx * (distance)) / MAP_S);
		check_y = (int)((g->player.y + g->player.dy * (distance)) / MAP_S);
		if (check_door_at(g, check_x, check_y))
			return ;
		distance++;
	}
}
