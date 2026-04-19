/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites_textures.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 13:34:25 by latabagl          #+#    #+#             */
/*   Updated: 2026/03/31 12:54:45 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_sprites_tex(t_game *g)
{
	int	i;

	if (!g || !g->mlx)
		return ;
	i = 0;
	while (i < 6)
	{
		if (g->spr_tex[i].img)
			mlx_destroy_image(g->mlx, g->spr_tex[i].img);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		if (g->gun.frames[i].img)
			mlx_destroy_image(g->mlx, g->gun.frames[i].img);
		i++;
	}
}

void	load_sprite_tex(t_game *g)
{
	if (!load_texture("textures/ghost1.xpm", &g->spr_tex[0], g)
		|| !load_texture("textures/ghost22.xpm", &g->spr_tex[1], g)
		|| !load_texture("textures/ghost33.xpm", &g->spr_tex[2], g)
		|| !load_texture("textures/ghost44.xpm", &g->spr_tex[3], g)
		|| !load_texture("textures/fruit.xpm", &g->spr_tex[4], g)
		|| !load_texture("textures/food.xpm", &g->spr_tex[5], g))
	{
		ft_putstr_fd("Error\nError loading a texture\n", 2);
		clean_exit_game(g);
	}
}

void	load_gun_tex(t_game *g)
{
	if (!load_texture("textures/gun1.xpm", &g->gun.frames[0], g)
		|| !load_texture("textures/gun2.xpm", &g->gun.frames[1], g)
		|| !load_texture("textures/gun3.xpm", &g->gun.frames[2], g)
		|| !load_texture("textures/gun4.xpm", &g->gun.frames[3], g)
		|| !load_texture("textures/gun5.xpm", &g->gun.frames[4], g))
	{
		ft_putstr_fd("Error\nError loading a texture\n", 2);
		clean_exit_game(g);
	}
}
