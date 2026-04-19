/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_texture_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:29:13 by latabagl          #+#    #+#             */
/*   Updated: 2026/04/02 08:44:48 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	assign_door_texture(t_game *g, t_ray *ray, t_wall *wall)
{
	int		i;
	float	hit_x;
	float	hit_y;

	if (!g->map.doors || g->map.doors_nb == 0)
		return ;
	hit_x = ray->v_hit_x;
	hit_y = ray->v_hit_y;
	if (wall->wall_dir == N || wall->wall_dir == S)
	{
		hit_x = ray->h_hit_x;
		hit_y = ray->h_hit_y;
	}
	i = 0;
	while (i < g->map.doors_nb)
	{
		if ((int)(hit_x / MAP_S) == g->map.doors[i].x
		&& (int)(hit_y / MAP_S) == g->map.doors[i].y)
		{
			wall->text = g->tex.door;
			return ;
		}
		i++;
	}
}

void	check_boundaries(t_wall *wall)
{
	if (wall->tx < 0)
		wall->tx = 0;
	if (wall->tx >= wall->text.height)
		wall->tx = wall->text.height - 1;
	if (wall->ty < 0)
		wall->ty = 0;
	if (wall->ty >= wall->text.height)
		wall->ty = wall->text.height - 1;
}
