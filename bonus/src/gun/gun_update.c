/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:15:41 by latabagl          #+#    #+#             */
/*   Updated: 2026/04/02 23:53:40 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	weapon_expired(t_game *g)
{
	g->gun.timer -= g->delta_time;
	if (g->gun.timer <= 0.0f)
	{
		g->gun.active = 0;
		g->gun.ammo = 0;
		g->gun.state = GUN_IDLE;
		ft_putstr_fd("Weapon expired!\n", 1);
		return (1);
	}
	return (0);
}

static int	out_of_ammo(t_game *g)
{
	if (g->gun.ammo <= 0)
	{
		if (g->gun.state == GUN_FIRING || g->gun.state == GUN_FIRE_START)
		{
			g->gun.state = GUN_FIRE_END;
			g->gun.anim_timer = 0.0f;
		}
		animate_gun(&g->gun);
		return (1);
	}
	return (0);
}

/*
** Updates gun logic:
** - handles expiration and ammo
** - handles fire cooldown and shooting
** - handles animation
*/
void	update_gun(t_game *g)
{
	if (!g->gun.active)
		return ;
	if (weapon_expired(g))
		return ;
	if (out_of_ammo(g))
		return ;
	if (g->gun.fire_cooldown > 0.0f)
		g->gun.fire_cooldown -= g->delta_time;
	if (g->keys.space && g->gun.fire_cooldown <= 0.0f)
		player_shoot(g);
	if (!g->keys.space && g->gun.fire_cooldown <= 0.0f)
	{
		if (g->gun.state == GUN_FIRING)
		{
			g->gun.state = GUN_FIRE_END;
			g->gun.anim_timer = 0.0f;
		}
	}
	g->gun.anim_timer += g->delta_time;
	animate_gun(&g->gun);
}
