/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:30:43 by latabagl          #+#    #+#             */
/*   Updated: 2026/03/27 14:00:17 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Computes the horizontal texture coordinate for the wall slice.
** Flips it for east and north facing walls
** so that textures are rendered in the correct direction.
*/
static void	compute_tx(t_ray *ray, t_wall *wall)
{
	if (wall->wall_dir == W)
		wall->tx = ((int) ray->v_hit_y & (MAP_S - 1)) * wall->text.map_scale;
	else if (wall->wall_dir == E)
	{
		wall->tx = ((int) ray->v_hit_y & (MAP_S - 1)) * wall->text.map_scale;
		wall->tx = wall->text.height - 1 - wall->tx;
	}
	else if (wall->wall_dir == S)
		wall->tx = ((int) ray->h_hit_x & (MAP_S - 1)) * wall->text.map_scale;
	else if (wall->wall_dir == N)
	{
		wall->tx = ((int) ray->h_hit_x & (MAP_S - 1)) * wall->text.map_scale;
		wall->tx = wall->text.height - 1 - wall->tx;
	}
}

/*
** Computes the vertical texture parameters for the wall slice.
** ty_step is the texture-to-screen scaling factor.
** If the projected wall exceeds the screen height,
** ty_off skips the invisible upper part of the texture.
*/
static void	compute_ty(t_wall *wall)
{
	wall->ty_off = 0;
	wall->ty_step = (float)wall->text.height / (float)wall->line_h;
	if (wall->line_h > WIN_HEIGHT)
	{
		wall->ty_off = (wall->line_h - WIN_HEIGHT) >> 1;
		wall->line_h = WIN_HEIGHT;
	}
	wall->ty = wall->ty_step * wall->ty_off;
	wall->line_offset = (WIN_HEIGHT >> 1) - (wall->line_h >> 1);
}

/*
** Applies shading to vertical walls (E/W).
** Extracts the RGB components, scales them by the shading factor
** and reconstructs the final color value
*/
static void	apply_shading(t_wall *wall, int *color, float shade)
{
	int	red;
	int	green;
	int	blue;

	if (wall->wall_dir == E || wall->wall_dir == W)
	{
		red = (*color >> 16) & 0xFF;
		green = (*color >> 8) & 0xFF;
		blue = (*color) & 0xFF;
		red = (int)(red * shade);
		green = (int)(green * shade);
		blue = (int)(blue * shade);
		*color = (red << 16) | (green << 8) | blue;
	}
}

/*
** Draws the vertical wall slice corresponding to a ray:
** - computes the horizontal screen range covered by the ray
** - retrieves the texture pixel color for each row of the slice
** - draws horizontal lines from the top to the bottom of the slice
**   into the image buffer
*/
static void	draw_wall(t_game *g, t_ray *ray, t_wall *wall)
{
	int		i;
	int		x;
	int		x1;
	int		color;
	t_line	line;

	x = (int)(ray->index * g->px_per_ray);
	x1 = (int)((ray->index + 1) * g->px_per_ray) - 1;
	if (x1 >= WIN_WIDTH)
		x1 = WIN_WIDTH - 1;
	i = 0;
	while (i < wall->line_h)
	{
		color = *(unsigned int *)(wall->text.buffer
				+ ((int)wall->ty & (wall->text.height - 1))
				* wall->text.line_len
				+ ((int)wall->tx & (wall->text.width - 1))
				* (wall->text.bpp >> 3));
		apply_shading(wall, &color, SHADE);
		line = init_line(x, wall->line_offset + i, x1, wall->line_offset + i);
		draw_line(&g->img, &line, color);
		wall->ty += wall->ty_step;
		i++;
	}
}

/*
** Determines the wall texture for a ray, computes its texture coordinates
** and renders the corresponding vertical wall slice.
*/
void	apply_texture(t_game *g, t_ray *ray, t_wall *wall)
{
	get_wall_orientation(g, ray, wall);
	compute_tx(ray, wall);
	compute_ty(wall);
	check_boundaries(wall);
	draw_wall(g, ray, wall);
}
