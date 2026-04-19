/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:13:59 by latabagl          #+#    #+#             */
/*   Updated: 2026/04/02 18:54:11 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Draws the scaled gun sprite into the image buffer
*/
static void	draw_gun_sprite(t_game *g, t_gun_draw *gun_draw)
{
	int		screen_x;
	int		screen_y;
	int		tex_x;
	int		tex_y;
	int		color;

	screen_y = 0;
	while (screen_y < gun_draw->gun_h)
	{
		screen_x = 0;
		while (screen_x < gun_draw->gun_w)
		{
			tex_x = screen_x * gun_draw->tex->width / gun_draw->gun_w;
			tex_y = screen_y * gun_draw->tex->height / gun_draw->gun_h;
			color = get_spr_pixel(gun_draw->tex, tex_x, tex_y);
			if (!is_transparent(color))
				put_pixel(&g->img, gun_draw->x + screen_x,
					gun_draw->y + screen_y, color);
			screen_x++;
		}
		screen_y++;
	}
}

/*
** Renders the gun:
** - Gets the current gun animation frame
** - Sets the width and height of the gun
** - Sets the position where the gun will be drawn
** - Draws the gun sprite
*/
void	render_gun(t_game *g)
{
	t_gun_draw	gun_draw;

	if (!g->gun.active)
		return ;
	gun_draw.tex = &g->gun.frames[g->gun.current_frame];
	gun_draw.gun_w = 480;
	gun_draw.gun_h = 480;
	gun_draw.x = (WIN_WIDTH - gun_draw.gun_w) / 2;
	gun_draw.y = WIN_HEIGHT - gun_draw.gun_h;
	draw_gun_sprite(g, &gun_draw);
}

static char	*itoa_wrapper(t_game *g, int number, char *ammo_str)
{
	char	*str;

	str = ft_itoa(number);
	if (!str)
	{
		if (ammo_str)
			free(ammo_str);
		ft_putstr_fd("Error\nMemory allocation failed\n", 2);
		clean_exit_game(g);
	}
	return (str);
}

/*
** Renders gun HUD: ammo counter and gun timer
*/
void	render_gun_hud(t_game *g)
{
	char	*ammo_str;
	char	*timer_str;
	int		timer_int;

	if (!g->gun.active)
		return ;
	ammo_str = itoa_wrapper(g, g->gun.ammo, NULL);
	mlx_string_put(g->mlx, g->win, WIN_WIDTH - 150, WIN_HEIGHT - 30,
		0xFFFFFF, "AMMO: ");
	mlx_string_put(g->mlx, g->win, WIN_WIDTH - 80, WIN_HEIGHT - 30,
		0xFFFF00, ammo_str);
	timer_int = (int)g->gun.timer;
	timer_str = itoa_wrapper(g, timer_int, ammo_str);
	mlx_string_put(g->mlx, g->win, 20, WIN_HEIGHT - 30,
		0xFFFFFF, "TIME: ");
	mlx_string_put(g->mlx, g->win, 90, WIN_HEIGHT - 30,
		0x00FF00, timer_str);
	free(ammo_str);
	free(timer_str);
}
