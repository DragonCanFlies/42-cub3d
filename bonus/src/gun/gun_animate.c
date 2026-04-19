/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_animate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:10:41 by latabagl          #+#    #+#             */
/*   Updated: 2026/04/02 22:38:21 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** GUN_IDLE
*/
static void	handle_gun_idle(t_gun *gun)
{
	gun->current_frame = 0;
	gun->anim_timer = 0.0f;
}

/*
** GUN_FIRE_START
*/
static void	handle_gun_fire_start(t_gun *gun)
{
	gun->current_frame = 1;
	if (gun->anim_timer >= GUN_ANIM_SPEED)
	{
		gun->state = GUN_FIRING;
		gun->current_frame = 2;
		gun->anim_timer = 0.0f;
	}
}

/*
** GUN_FIRING
** Cycles between frames 2 and 3 while firing.
** Last else: Resets if out of sync
*/
static void	handle_gun_firing(t_gun *gun)
{
	if (gun->anim_timer >= GUN_ANIM_SPEED)
	{
		if (gun->current_frame == 2)
			gun->current_frame = 3;
		else if (gun->current_frame == 3)
			gun->current_frame = 2;
		else
			gun->current_frame = 2;
		gun->anim_timer = 0.0f;
	}
}

/*
** GUN_FIRE_END
*/
static void	handle_gun_fire_end(t_gun *gun)
{
	gun->current_frame = 4;
	if (gun->anim_timer >= GUN_ANIM_SPEED)
	{
		gun->state = GUN_IDLE;
		gun->current_frame = 0;
		gun->anim_timer = 0.0f;
	}
}

/*
** Clamps the current frame inside valid range [0-4].
** Updates the current frame and the animation
** timer based on the gun state.
*/
void	animate_gun(t_gun *gun)
{
	if (gun->current_frame < 0)
		gun->current_frame = 0;
	if (gun->current_frame > 4)
		gun->current_frame = 4;
	if (gun->state == GUN_IDLE)
		handle_gun_idle(gun);
	else if (gun->state == GUN_FIRE_START)
		handle_gun_fire_start(gun);
	else if (gun->state == GUN_FIRING)
		handle_gun_firing(gun);
	else if (gun->state == GUN_FIRE_END)
		handle_gun_fire_end(gun);
}
