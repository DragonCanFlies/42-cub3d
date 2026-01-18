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

int is_transparent(int color)
{
	return ((color & 0x00FFFFFF) == 0x00FF00FF);
}
int	check_zbuffer(t_game *g, int x, float dist)
{
	if (x < 0 || x >= WIN_WIDTH)
		return (0);
	return (g->zbuffer[x] > dist);
}