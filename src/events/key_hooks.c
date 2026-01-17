/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 19:23:51 by latabagl          #+#    #+#             */
/*   Updated: 2026/01/17 19:24:12 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_game *game)
{
	clean_exit_game(game);
	return (0);
}

// macOS
int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_window(game);
	if (keycode == KEY_W)
		game->keys.w = 1;
	if (keycode == KEY_A)
		game->keys.a = 1;
	if (keycode == KEY_S)
		game->keys.s = 1;
	if (keycode == KEY_D)
		game->keys.d = 1;
	if (keycode == KEY_LEFT)
		game->keys.left = 1;
	if (keycode == KEY_RIGHT)
		game->keys.right = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.w = 0;
	if (keycode == KEY_A)
		game->keys.a = 0;
	if (keycode == KEY_S)
		game->keys.s = 0;
	if (keycode == KEY_D)
		game->keys.d = 0;
	if (keycode == KEY_LEFT)
		game->keys.left = 0;
	if (keycode == KEY_RIGHT)
		game->keys.right = 0;
	return (0);
}

// linux
// #include <X11/keysym.h>
// int	key_press(int keycode, t_game *game)
// {
// 	if (keycode == XK_Escape)
// 		close_window(game);
// 	if (keycode == XK_z)
// 		game->keys.w = 1;
// 	if (keycode == XK_q)
// 		game->keys.a = 1;
// 	if (keycode == XK_s)
// 		game->keys.s = 1;
// 	if (keycode == XK_d)
// 		game->keys.d = 1;
// 	if (keycode == XK_Left)
// 		game->keys.left = 1;
// 	if (keycode == XK_Right)
// 		game->keys.right = 1;
// 	return (0);
// }

// int	key_release(int keycode, t_game *game)
// {
// 	if (keycode == XK_z)
// 		game->keys.w = 0;
// 	if (keycode == XK_q)
// 		game->keys.a = 0;
// 	if (keycode == XK_s)
// 		game->keys.s = 0;
// 	if (keycode == XK_d)
// 		game->keys.d = 0;
// 	if (keycode == XK_Left)
// 		game->keys.left = 0;
// 	if (keycode == XK_Right)
// 		game->keys.right = 0;
// 	return (0);
// }