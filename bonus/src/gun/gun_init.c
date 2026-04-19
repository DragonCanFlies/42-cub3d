/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:13:22 by latabagl          #+#    #+#             */
/*   Updated: 2026/02/03 15:35:25 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_gun(t_game *g)
{
	load_gun_tex(g);
	g->gun.current_frame = 0;
	g->gun.state = GUN_IDLE;
	g->gun.ammo = 0;
	g->gun.timer = 0.0f;
	g->gun.active = 0;
	g->gun.fire_cooldown = 0.0f;
	g->gun.anim_timer = 0.0f;
}
