/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:23:54 by latabagl          #+#    #+#             */
/*   Updated: 2026/03/24 18:16:23 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Returns 1 if a door is at location (x, y)
*/
static int	door_is_found(t_game *g, int x, int y, int i)
{
	return ((x == g->map.doors[i].x)
		&& (y == g->map.doors[i].y));
}

/*
** Opens the door and replaces the tile on the map with '0'
*/
static void	open_door(t_game *g, int i, int p)
{
	g->map.doors[i].open = 1;
	g->map.map_data[p] = 0;
}

/*
** If the player is not standing on the door tile,
** closes the door and replaces the tile on the map with '1'
*/
static void	close_door(t_game *g, int i, int p)
{
	if (!(g->player.x == g->map.doors[i].x
			&& g->player.y == g->map.doors[i].y))
	{
		g->map.doors[i].open = 0;
		g->map.map_data[p] = 1;
	}
}

/*
** Given tile coordinates (x, y), checks if a door exists on that tile
** and opens a closed door or closes an open door.
** Prevents closing a door if the player is standing on the door tile.
*/
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
		if (door_is_found(g, x, y, i))
		{
			if (g->map.doors[i].open == 0)
				open_door(g, i, p);
			else if (g->map.doors[i].open == 1)
				close_door(g, i, p);
			return (1);
		}
		i++;
	}
	return (0);
}

/*
** Called when key E is pressed
** Casts a short ray in the player's looking direction to check for a door
** and interact with a door
*/
void	interact_with_door(t_game *g)
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
