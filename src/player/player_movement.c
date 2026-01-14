#include "cub3d.h"


static int	pos_is_valid(t_game *g, float new_x, float new_y)
{
	int		mx;
	int		my;
	int		mp;

	mx = (int)(new_x) >> 6;
	my = (int)(new_y) >> 6;
	mp = my * g->map.x + mx;
	return (mp >= 0 && mp < g->map.x * g->map.y && g->map.map_data[mp] == 0);
}

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

static void	rotate_player(t_game *game, float rotation)
{
	game->player.angle += rotation;
	game->player.angle = fix_angle(game->player.angle);
	game->player.dx = cos(deg_to_rad(game->player.angle));
	game->player.dy = -sin(deg_to_rad(game->player.angle));
}

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
	if (pos_is_valid(game, new_x, new_y))
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}
