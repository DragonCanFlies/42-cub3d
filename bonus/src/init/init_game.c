/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 19:25:03 by latabagl          #+#    #+#             */
/*   Updated: 2026/04/05 17:33:50 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_game_bonus(t_game *g)
{
	init_sprites(g);
	init_gun(g);
	g->health = PLAYER_MAX_HEALTH;
	g->max_health = PLAYER_MAX_HEALTH;
	g->damage_cooldown = 0.0f;
	g->max_sprite_size = WIN_HEIGHT << 1;
	g->inv_ray_acc = 1.0f / RAY_ACC;
	g->rad_to_deg = 180.0f / M_PI;
	g->half_fov = FOV * 0.5f;
}

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
		clean_exit_game(g);
	g->img.img = mlx_new_image(g->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!g->img.img)
		clean_exit_game(g);
	g->img.buffer = mlx_get_data_addr(g->img.img, &g->img.bpp,
			&g->img.line_len, &g->img.endian);
	g->px_per_ray = (WIN_WIDTH * RAY_ACC) / FOV;
	if (fmod((WIN_WIDTH * RAY_ACC), FOV) != 0)
		ft_putstr_fd(ERR_PPR, 2);
	ft_bzero(&g->keys, sizeof(g->keys));
	init_texture(g);
	init_game_bonus(g);
}
