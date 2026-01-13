#include "cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	unsigned int	*dst;
	int				buffer_placement;
	
	if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
		return;
	buffer_placement = (y * img->line_len) + (x * (img->bpp / 8));
	dst = (unsigned int *)(img->buffer + buffer_placement);
	*dst = color;
}

void	draw_rect(t_img *img, int x, int y, int w, int h, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			put_pixel(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_line(t_img *img, t_line *l, int color)
{
	int e2;

	while (1)
	{
		put_pixel(img, l->x1, l->y1, color);
		if (l->x1 == l->x2 && l->y1 == l->y2)
			break;
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

t_line	init_line(int x1, int y1, int x2, int y2)
{
	t_line	line;

	line.x1 = x1;
	line.x2 = x2;
	line.y1 = y1;
	line.y2	= y2;
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

int	render(t_game *game)
{
	int	i;

	i = 0;
	while (i < WIN_WIDTH * WIN_HEIGHT)
	{
		((int *)game->img.buffer)[i] = 0x4C4C4C;  // Medium gray
		i++;
	}
	update_player(game);
	//draw_map_2d(game);      // 2D top-down map (left side)
	ray_caster(game);     // 3D raycasted view (right side)
	//draw_player_2d(game);   // Player indicator on 2D map
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
