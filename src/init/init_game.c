/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 19:25:03 by latabagl          #+#    #+#             */
/*   Updated: 2026/03/22 20:42:53 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Initializes the game: starts the graphics engine, creates the game window,
** creates the render image and retrieves its pixel buffer,
** and initializes input keys and textures
*/
void	init_game(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
	{
		print_error("MLX init failed\n");
		clean_exit_game(g);
	}
	g->win = mlx_new_window(g->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!g->win)
	{
		print_error("Window creation failed\n");
		clean_exit_game(g);
	}
	g->img.img = mlx_new_image(g->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!g->img.img)
	{
		print_error("Window image creation failed\n");
		clean_exit_game(g);
	}
	g->img.buffer = mlx_get_data_addr(g->img.img, &g->img.bpp,
			&g->img.line_len, &g->img.endian);
	g->px_per_ray = (WIN_WIDTH * RAY_ACC) / FOV;
	if (fmod((WIN_WIDTH * RAY_ACC), FOV) != 0)
		ft_putstr_fd(ERR_PPR, 2);
	ft_bzero(&g->keys, sizeof(g->keys));
	init_texture(g);
}
