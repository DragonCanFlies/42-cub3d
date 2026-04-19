/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:49:05 by latabagl          #+#    #+#             */
/*   Updated: 2026/02/03 18:51:55 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_pixel_safe(t_game *g, int x, int y, int color)
{
	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	if (!is_transparent(color))
		put_pixel(&g->img, x, y, color);
}

static void	draw_column(t_game *g, t_sprite *s, t_spr_draw *d, int x)
{
	int		y;
	int		tex_x;
	int		tex_y;
	int		color;
	t_img	*tex;

	if (!check_zbuffer(g, x, d->dist_y))
		return ;
	tex = &g->spr_tex[s->tex_id];
	tex_x = calc_tex_x(x, d, tex->width);
	y = -d->height / 2 + WIN_HEIGHT / 2;
	if (y < 0)
		y = 0;
	while (y < d->height / 2 + WIN_HEIGHT / 2 && y < WIN_HEIGHT)
	{
		tex_y = calc_tex_y(y, d, tex->height);
		color = get_spr_pixel(tex, tex_x, tex_y);
		draw_pixel_safe(g, x, y, color);
		y++;
	}
}

static void	calc_bounds(t_spr_draw *d, t_spr_bounds *b)
{
	b->start_y = -(d->height >> 1) + (WIN_HEIGHT >> 1);
	b->end_y = (d->height >> 1) + (WIN_HEIGHT >> 1);
	b->start_x = -(d->width >> 1) + d->scr_x;
	b->end_x = (d->width >> 1) + d->scr_x;
	if (b->start_y < 0)
		b->start_y = 0;
	if (b->end_y >= WIN_HEIGHT)
		b->end_y = WIN_HEIGHT - 1;
	if (b->start_x < 0)
		b->start_x = 0;
	if (b->end_x >= WIN_WIDTH)
		b->end_x = WIN_WIDTH - 1;
}

void	draw_sprite_cols(t_game *g, t_sprite *s, t_spr_draw *d, t_spr_bounds *b)
{
	int	x;

	x = b->start_x;
	while (x < b->end_x)
	{
		draw_column(g, s, d, x);
		x++;
	}
}

void	draw_sprite(t_game *g, t_sprite *s)
{
	t_spr_draw		d;
	t_spr_bounds	b;

	transform_sprite(g, s, &d);
	if (d.dist_y <= 0)
		return ;
	calc_bounds(&d, &b);
	draw_sprite_cols(g, s, &d, &b);
}
