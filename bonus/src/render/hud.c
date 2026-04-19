/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:23:12 by latabagl          #+#    #+#             */
/*   Updated: 2026/04/02 08:41:10 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_black_background(t_game *g, int bar_height, int bar_width)
{
	int	i;
	int	j;

	j = 0;
	while (j < bar_height)
	{
		i = 0;
		while (i < bar_width)
		{
			put_pixel(&g->img, HUD_OFFSET + i, HUD_OFFSET + j, 0x000000);
			i++;
		}
		j++;
	}
}

static void	draw_health_bar(t_game *g, int bar_height,
		int health_width, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < bar_height)
	{
		i = 0;
		while (i < health_width)
		{
			put_pixel(&g->img, HUD_OFFSET + i, HUD_OFFSET + j, color);
			i++;
		}
		j++;
	}
}

static void	draw_white_border(t_game *g, int bar_width, int bar_height)
{
	int	i;
	int	j;

	i = 0;
	while (i < bar_width)
	{
		put_pixel(&g->img, HUD_OFFSET + i, HUD_OFFSET, 0xFFFFFF);
		put_pixel(&g->img, HUD_OFFSET + i,
			HUD_OFFSET + bar_height - 1, 0xFFFFFF);
		i++;
	}
	j = 0;
	while (j < bar_height)
	{
		put_pixel(&g->img, HUD_OFFSET, HUD_OFFSET + j, 0xFFFFFF);
		put_pixel(&g->img, HUD_OFFSET + bar_width - 1,
			HUD_OFFSET + j, 0xFFFFFF);
		j++;
	}
}

static void	render_health_bar(t_game *g)
{
	int	bar_width;
	int	bar_height;
	int	health_width;
	int	color;

	bar_width = 200;
	bar_height = 20;
	health_width = (g->health * bar_width) / g->max_health;
	if (health_width < 0)
		health_width = 0;
	if (g->health < 30)
		color = 0xFF0000;
	else if (g->health < 60)
		color = 0xFFFF00;
	else
		color = 0x00FF00;
	draw_black_background(g, bar_height, bar_width);
	draw_health_bar(g, bar_height, health_width, color);
	draw_white_border(g, bar_width, bar_height);
}

/*
** Renders the player HUD:
** health bar, health text, fps counter,
** and "DAMAGED!" warning when taking damage
*/
void	render_player_hud(t_game *g)
{
	char			text[64];
	static float	elapsed = 0.0f;
	static int		frames = 0;
	static int		fps = 0;

	render_health_bar(g);
	snprintf(text, sizeof(text), "HP: %d/%d", g->health, g->max_health);
	mlx_string_put(g->mlx, g->win, 20, 50, 0xFFFFFF, text);
	elapsed += g->delta_time;
	frames++;
	if (elapsed >= 1.0f)
	{
		fps = frames;
		frames = 0;
		elapsed = 0.0f;
	}
	snprintf(text, sizeof(text), "FPS: %d", fps);
	mlx_string_put(g->mlx, g->win, 20, 80, 0xFFFF00, text);
	if (g->damage_cooldown > 0.0f)
	{
		mlx_string_put(g->mlx, g->win, WIN_WIDTH / 2 - 30, 50,
			0xFF0000, "DAMAGED!");
	}
}
