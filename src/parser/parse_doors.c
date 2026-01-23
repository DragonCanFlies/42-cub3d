/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_doors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 18:37:33 by latabagl          #+#    #+#             */
/*   Updated: 2026/01/21 16:33:57 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_doors_nb(t_game *g)
{
	int	row;
	int	col;
	int	count;

	count = 0;
	row = 0;
	while (g->map.raw_map[row])
	{
		col = 0;
		while (g->map.raw_map[row][col])
		{
			if (g->map.raw_map[row][col] == 'D')
				count++;
			col++;
		}
		row++;
	}
	return (count);
}

static void	fill_doors_info(t_game *g)
{
	int	row;
	int	col;
	int	i;

	i = 0;
	row = 0;
	while (g->map.raw_map[row])
	{
		col = 0;
		while (g->map.raw_map[row][col])
		{
			if (g->map.raw_map[row][col] == 'D')
			{
				g->map.doors[i].x = col;
				g->map.doors[i].y = row;
				g->map.doors[i].open = 0;
				i++;
			}
			col++;
		}
		row++;
	}
}

void	parse_doors(t_game *g)
{
	g->map.doors_nb = get_doors_nb(g);
	if (g->map.doors_nb == 0)
	{
		g->map.doors = NULL;
		return ;
	}
	g->map.doors = malloc(sizeof(t_door) * g->map.doors_nb);
	if (!g->map.doors)
		handle_error(MALLOC);
	fill_doors_info(g);
}
