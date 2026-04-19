/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_animate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:45:54 by latabagl          #+#    #+#             */
/*   Updated: 2026/03/31 12:58:36 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Updates the animation timer (frame_time) by adding delta_time
** Returns 1 when enough time has passed to update the animation frame
** and resets frame_time to zero
*/
static int	should_animate(float *frame_time, float speed, float delta_time)
{
	*frame_time += delta_time;
	if (*frame_time >= speed)
	{
		*frame_time = 0.0f;
		return (1);
	}
	return (0);
}

/*
** Advances the enemy animation when enough time has passed
** by selecting the next texture in the sequence
*/
void	animate_enemy(t_game *g, t_sprite *enemy)
{
	static float	frame_time;
	static int		frame;

	if (should_animate(&frame_time, E_ANIM_SPEED, g->delta_time))
	{
		frame = (frame + 1) % 4;
		enemy->tex_id = TEX_GHOST1 + frame;
	}
}
