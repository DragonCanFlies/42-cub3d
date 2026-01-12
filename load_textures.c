/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:51:42 by latabagl          #+#    #+#             */
/*   Updated: 2026/01/11 20:56:59 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_texture(char *path, t_img *texture, t_game *g)
{
	texture->img = mlx_xpm_file_to_image(g->mlx, path, &(texture->width), &(texture->height));
	if (!texture->img)
	{
		// TODO
		printf("Error loading texture\n");
		exit (1);
	}
	texture->buffer = mlx_get_data_addr(texture->img, &(texture->bpp), &(texture->line_len), &(texture->endian));
}

int	rgb_to_int(uint8_t *colors_input)
{
	int	color;

	color = 0;
	color = (colors_input[0] << 16) | (colors_input[1] << 8) | colors_input[2];
	return (color);
}
