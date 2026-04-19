/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:47:21 by latabagl          #+#    #+#             */
/*   Updated: 2026/02/03 18:48:44 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_spr_pixel(t_img *tex, int x, int y)
{
	int	pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	pixel = *(int *)(tex->buffer + (y * tex->line_len
				+ x * (tex->bpp / 8)));
	return (pixel);
}

int	calc_tex_x(int x, t_spr_draw *d, int tex_w)
{
	int	offset;
	int	tex_x;

	offset = -d->width / 2 + d->scr_x;
	tex_x = (x - offset) * tex_w / d->width;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex_w)
		tex_x = tex_w - 1;
	return (tex_x);
}

int	calc_tex_y(int y, t_spr_draw *d, int tex_h)
{
	int	offset;
	int	tex_y;

	offset = -d->height / 2 + WIN_HEIGHT / 2;
	tex_y = (y - offset) * tex_h / d->height;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= tex_h)
		tex_y = tex_h - 1;
	return (tex_y);
}

// Gun background, magenta
int	is_transparent(int color)
{
	if ((color & 0x00FFFFFF) == 0x00980088)
		return (1);
	if ((color & 0x00FFFFFF) == 0x00FF00FF)
		return (1);
	return (0);
}

int	check_zbuffer(t_game *g, int x, float dist)
{
	if (x < 0 || x >= WIN_WIDTH)
		return (0);
	return (g->zbuffer[x] > dist);
}
