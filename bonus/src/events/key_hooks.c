/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 19:23:51 by latabagl          #+#    #+#             */
/*   Updated: 2026/03/30 22:40:30 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_game *game)
{
	clean_exit_game(game);
	return (0);
}

int	mouse_move(int x, int y, t_game *game)
{
	int	dx;

	(void) y;
	if (!game->mouse.initialized)
	{
		game->mouse.x = x;
		game->mouse.initialized = 1;
		return (0);
	}
	dx = x - game->mouse.x;
	rotate_player(game, ROT_SPEED * -dx);
	game->mouse.x = x;
	return (0);
}

// macOS
// int	key_press(int keycode, t_game *game)
// {
// 	if (keycode == KEY_ESC)
// 		close_window(game);
// 	if (keycode == KEY_W)
// 		game->keys.w = 1;
// 	if (keycode == KEY_A)
// 		game->keys.a = 1;
// 	if (keycode == KEY_S)
// 		game->keys.s = 1;
// 	if (keycode == KEY_D)
// 		game->keys.d = 1;
// 	if (keycode == KEY_LEFT)
// 		game->keys.left = 1;
// 	if (keycode == KEY_RIGHT)
// 		game->keys.right = 1;
// 	if (keycode == 49 || keycode == 32)  // SPACE
// 		game->keys.space = 1;  // CHANGED: just set flag
// 	if (keycode == KEY_E)
// 		open_door(game);
// 	return (0);
// }

// int	key_release(int keycode, t_game *game)
// {
// 	if (keycode == KEY_W)
// 		game->keys.w = 0;
// 	if (keycode == KEY_A)
// 		game->keys.a = 0;
// 	if (keycode == KEY_S)
// 		game->keys.s = 0;
// 	if (keycode == KEY_D)
// 		game->keys.d = 0;
// 	if (keycode == KEY_LEFT)
// 		game->keys.left = 0;
// 	if (keycode == KEY_RIGHT)
// 		game->keys.right = 0;
	// if (keycode == 49 || keycode == 32)  // SPACE
	// 	game->keys.space = 0;  // ADD THIS
// 	return (0);
// }

//linux
int	key_press(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		close_window(game);
	if (keycode == XK_z)
		game->keys.w = 1;
	if (keycode == XK_q)
		game->keys.a = 1;
	if (keycode == XK_s)
		game->keys.s = 1;
	if (keycode == XK_d)
		game->keys.d = 1;
	if (keycode == XK_Left)
		game->keys.left = 1;
	if (keycode == XK_Right)
		game->keys.right = 1;
	if (keycode == XK_space)
		game->keys.space = 1;
	if (keycode == XK_e)
		interact_with_door(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == XK_z)
		game->keys.w = 0;
	if (keycode == XK_q)
		game->keys.a = 0;
	if (keycode == XK_s)
		game->keys.s = 0;
	if (keycode == XK_d)
		game->keys.d = 0;
	if (keycode == XK_Left)
		game->keys.left = 0;
	if (keycode == XK_Right)
		game->keys.right = 0;
	if (keycode == XK_space)
		game->keys.space = 0;
	return (0);
}
