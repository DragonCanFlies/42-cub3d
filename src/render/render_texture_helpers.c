/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_texture_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:29:13 by latabagl          #+#    #+#             */
/*   Updated: 2026/03/24 16:32:24 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Determines the wall orientation and selects the corresponding wall texture
*/
void	get_wall_orientation(t_game *g, t_ray *ray, t_wall *wall)
{
	if (ray->dis_v < ray->dis_h)
	{
		wall->text = g->tex.west;
		wall->wall_dir = W;
		if (cos(deg_to_rad(ray->ra)) < -0.001)
		{
			wall->text = g->tex.east;
			wall->wall_dir = E;
		}
	}
	else
	{
		wall->text = g->tex.south;
		wall->wall_dir = S;
		if (sin(deg_to_rad(ray->ra)) < -0.001)
		{
			wall->text = g->tex.north;
			wall->wall_dir = N;
		}
	}
}

/*
** Clamps the texture coordinates to the valid texture boundaries
*/
void	check_boundaries(t_wall *wall)
{
	if (wall->tx < 0)
		wall->tx = 0;
	if (wall->tx >= wall->text.width)
		wall->tx = wall->text.width - 1;
	if (wall->ty < 0)
		wall->ty = 0;
	if (wall->ty >= wall->text.height)
		wall->ty = wall->text.height - 1;
}
