/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tp.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:23:57 by latabagl          #+#    #+#             */
/*   Updated: 2026/03/24 18:04:04 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Returns 1 if the player is standing on the first teleportation tile,
** 2 if the player is standing on second teleportation tile, 
** 0 if the player is not standing on a teleportation tile
*/
static int	is_player_on_tp_tile(t_game *g)
{
	int	check_x;
	int	check_y;
	int	check_p;

	check_x = (int)(g->player.x / MAP_S);
	check_y = (int)(g->player.y / MAP_S);
	check_p = check_y * g->map.x + check_x;
	if (check_p < 0 || (check_p >= g->map.x * g->map.y))
		return (0);
	if ((check_x == g->map.tp.ax) && (check_y == g->map.tp.ay))
		return (1);
	if ((check_x == g->map.tp.bx) && (check_y == g->map.tp.by))
		return (2);
	return (0);
}

/*
** Teleports the player to the other teleportation tile
 */
static void	teleport_player(t_game *g, int tp)
{
	if (tp == 1)
	{
		g->player.x = (float) g->map.tp.bx * MAP_S + (MAP_S >> 1);
		g->player.y = (float) g->map.tp.by * MAP_S + (MAP_S >> 1);
	}
	else if (tp == 2)
	{
		g->player.x = (float) g->map.tp.ax * MAP_S + (MAP_S >> 1);
		g->player.y = (float) g->map.tp.ay * MAP_S + (MAP_S >> 1);
	}
}

/*
** If teleportation is enabled, checks wheter the player is standing on
** a teleportation tile and teleports them to the other tp tile
*/
void	handle_teleportation(t_game *g)
{
	int	tp;

	if (!g->map.tp.enabled)
		return ;
	tp = is_player_on_tp_tile(g);
	if (!g->map.tp.just_teleported && tp)
	{
		teleport_player(g, tp);
		g->map.tp.just_teleported = 1;
	}
	else if (g->map.tp.just_teleported && !tp)
		g->map.tp.just_teleported = 0;
}
