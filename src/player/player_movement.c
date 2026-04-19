/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 22:21:06 by latabagl          #+#    #+#             */
/*   Updated: 2026/03/25 19:11:48 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Returns 1 if location (x, y) is inside a wall or outside the map
*/
static int	is_inside_wall(t_game *g, int x, int y)
{
	int	mp;

	mp = (y / MAP_S) * g->map.x + (x / MAP_S);
	if (mp < 0 || mp >= g->map.x * g->map.y || g->map.map_data[mp] == 1)
		return (1);
	return (0);
}

/* 
** Collision zone around player is a square.
** Checks top left, top right, center, bottom left and bottom right 
** of the square. Returns 1 is player position is valid.
*/
static int	pos_is_valid(t_game *g, float new_x, float new_y)
{
	int	r;

	r = PLAYER_RADIUS;
	if (is_inside_wall(g, (int)(new_x - r), (int)(new_y - r)))
		return (0);
	if (is_inside_wall(g, (int)(new_x + r), (int)(new_y - r)))
		return (0);
	if (is_inside_wall(g, (int)(new_x), (int)(new_y)))
		return (0);
	if (is_inside_wall(g, (int)(new_x - r), (int)(new_y + r)))
		return (0);
	if (is_inside_wall(g, (int)(new_x + r), (int)(new_y + r)))
		return (0);
	return (1);
}

/*
** Applies forward, backward and lateral movements
*/
static void	move_player(t_game *game, float *new_x, float *new_y)
{
	if (game->keys.w)
	{
		*new_x += game->player.dx * MOVE_SPEED;
		*new_y += game->player.dy * MOVE_SPEED;
	}
	if (game->keys.a)
	{
		*new_x += game->player.dy * MOVE_SPEED;
		*new_y -= game->player.dx * MOVE_SPEED;
	}
	if (game->keys.s)
	{
		*new_x -= game->player.dx * MOVE_SPEED;
		*new_y -= game->player.dy * MOVE_SPEED;
	}
	if (game->keys.d)
	{
		*new_x -= game->player.dy * MOVE_SPEED;
		*new_y += game->player.dx * MOVE_SPEED;
	}
}

/*
** Rotates the player's view and updates the direction vector
*/
void	rotate_player(t_game *game, float rotation)
{
	game->player.angle += rotation;
	game->player.angle = fix_angle(game->player.angle);
	game->player.dx = cos(deg_to_rad(game->player.angle));
	game->player.dy = -sin(deg_to_rad(game->player.angle));
}

/*
** Updates player movement: applies rotation,
** computes the player's new position and moves the player
** if the location is valid
*/
void	update_player(t_game *game)
{
	float	new_x;
	float	new_y;

	new_x = game->player.x;
	new_y = game->player.y;
	if (game->keys.left)
		rotate_player(game, ROT_SPEED);
	if (game->keys.right)
		rotate_player(game, -ROT_SPEED);
	move_player(game, &new_x, &new_y);
	if (pos_is_valid(game, new_x, game->player.y))
		game->player.x = new_x;
	if (pos_is_valid(game, game->player.x, new_y))
		game->player.y = new_y;
}
