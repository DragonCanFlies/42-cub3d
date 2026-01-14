
#include "cub3d.h"

int	load_texture(char *path, t_img *texture, t_game *g)
{
	texture->img = mlx_xpm_file_to_image(g->mlx, path, &(texture->width), &(texture->height));
	if (!texture->img)
		return (0);
	texture->buffer = mlx_get_data_addr(texture->img, &(texture->bpp), &(texture->line_len), &(texture->endian));
	return (1);
}

int	rgb_to_int(uint8_t *colors_input)
{
	int	color;

	color = 0;
	color = (colors_input[0] << 16) | (colors_input[1] << 8) | colors_input[2];
	return (color);
}

void	destroy_images(t_game *g)
{
	if (g->tex.north.img)
		mlx_destroy_image(g->mlx, g->tex.north.img);
	if (g->tex.south.img)
		mlx_destroy_image(g->mlx, g->tex.south.img);
	if (g->tex.east.img)
		mlx_destroy_image(g->mlx, g->tex.east.img);
	if (g->tex.west.img)
		mlx_destroy_image(g->mlx, g->tex.west.img);
}

void	init_texture(t_game *g)
{
	if (!load_texture(g->map.north_path, &g->tex.north, g)
	|| !load_texture(g->map.south_path, &g->tex.south, g)
	|| !load_texture(g->map.east_path, &g->tex.east, g)
	|| !load_texture(g->map.west_path, &g->tex.west, g))
	{
		// exit cleanly
		ft_putstr_fd("Error\nError loading a texture\n", 2);
		// probably img of game must be freed too
		destroy_images(g);
		mlx_destroy_window(g->mlx, g->win);
		mlx_destroy_display(g->mlx);
		free(g->mlx);
		exit (1);
	}
	g->tex.floor = rgb_to_int(g->map.floor);
	g->tex.ceiling = rgb_to_int(g->map.ceiling);
}
