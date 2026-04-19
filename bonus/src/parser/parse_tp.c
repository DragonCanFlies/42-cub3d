/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 12:44:46 by latabagl          #+#    #+#             */
/*   Updated: 2026/01/21 15:53:13 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_tp_info(t_game *g, int tp_nb, int col, int row)
{
	if (tp_nb == 1)
	{
		g->map.tp.ax = col;
		g->map.tp.ay = row;
	}
	else if (tp_nb == 2)
	{
		g->map.tp.bx = col;
		g->map.tp.by = row;
	}
}

// teleportation is enabled if there are two T on the map
void	parse_tp(t_game *g)
{
	int	row;
	int	col;
	int	tp_nb;

	g->map.tp.enabled = 0;
	g->map.tp.just_teleported = 0;
	tp_nb = 0;
	row = 0;
	while (g->map.raw_map[row])
	{
		col = 0;
		while (g->map.raw_map[row][col])
		{
			if (g->map.raw_map[row][col] == 'T')
			{
				tp_nb++;
				fill_tp_info(g, tp_nb, col, row);
			}
			col++;
		}
		row++;
	}
	if (tp_nb == 2)
		g->map.tp.enabled = 1;
}
