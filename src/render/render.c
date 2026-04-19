/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:02:48 by latabagl          #+#    #+#             */
/*   Updated: 2026/03/23 21:28:33 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Sets the color of a pixel at (x, y) in the image buffer
** by jumping to the correct row and then the correct pixel in that row
*/
void	put_pixel(t_img *img, int x, int y, int color)
{
	unsigned int	*dst;
	int				buffer_placement;

	if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
		return ;
	buffer_placement = (y * img->line_len) + (x * (img->bpp >> 3));
	dst = (unsigned int *)(img->buffer + buffer_placement);
	*dst = color;
}

/*
** Draws a line between two points using Bresenham’s line algorithm
*/
void	draw_line(t_img *img, t_line *l, int color)
{
	int	e2;

	while (1)
	{
		put_pixel(img, l->x1, l->y1, color);
		if (l->x1 == l->x2 && l->y1 == l->y2)
			break ;
		e2 = 2 * l->err;
		if (e2 > -l->dy)
		{
			l->err -= l->dy;
			l->x1 += l->sx;
		}
		if (e2 < l->dx)
		{
			l->err += l->dx;
			l->y1 += l->sy;
		}
	}
}

/*
** Initializes and returns a t_line structure containing all values required
** to draw a line between two points using Bresenham’s line algorithm
*/
t_line	init_line(int x1, int y1, int x2, int y2)
{
	t_line	line;

	line.x1 = x1;
	line.x2 = x2;
	line.y1 = y1;
	line.y2 = y2;
	line.dx = abs(x2 - x1);
	line.dy = abs(y2 - y1);
	if (x1 < x2)
		line.sx = 1;
	else
		line.sx = -1;
	if (y1 < y2)
		line.sy = 1;
	else
		line.sy = -1;
	line.err = line.dx - line.dy;
	return (line);
}

/*
** Render loop: fills the image buffer with ceiling and floor colors,
** updates player movement, performs raycasting to render walls,
** and displays the final image in the window
*/
int	render(t_game *game)
{
	int	i;
	int	half;
	int	total;
	int	*pixels;

	total = WIN_WIDTH * WIN_HEIGHT;
	half = total >> 1;
	pixels = (int *)game->img.buffer;
	i = 0;
	while (i < half)
		pixels[i++] = game->tex.ceiling;
	while (i < total)
		pixels[i++] = game->tex.floor;
	update_player(game);
	ray_caster(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
