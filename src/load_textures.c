/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:51:42 by latabagl          #+#    #+#             */
/*   Updated: 2026/01/13 20:35:12 by loasaad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	destroy_images(t_game *game)
{
	if (game->north.img)
		mlx_destroy_image(game->mlx, game->north.img);
	if (game->south.img)
		mlx_destroy_image(game->mlx, game->south.img);
	if (game->east.img)
		mlx_destroy_image(game->mlx, game->east.img);
	if (game->west.img)
		mlx_destroy_image(game->mlx, game->west.img);
}

void	load_img_colors(t_game *game, t_map *config)
{
	if (!load_texture(config->north_path, &game->north, game)
	|| !load_texture(config->south_path, &game->south, game)
	|| !load_texture(config->east_path, &game->east, game)
	|| !load_texture(config->west_path, &game->west, game))
	{
		// exit cleanly
		ft_putstr_fd("Error\nError loading a texture\n", 2);
		// probably img of game must be freed too
		destroy_images(game);
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		exit (1);
	}
	game->floor = rgb_to_int(config->floor);
	game->ceiling = rgb_to_int(config->ceiling);
}
