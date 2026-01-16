/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closed_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:18:07 by latabagl          #+#    #+#             */
/*   Updated: 2026/01/15 18:42:58 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_copy(char **copy)
{
	int	i;

	i = 0;
	while (copy[i])
	{
		free(copy[i]);
		i++;
	}
	free(copy);
}

static void	flood_fill(char **copy, int x, int y, t_game *g)
{
	if (x < 0 || x >= g->map.x || y < 0 || y >= g->map.y)
	{
		free_copy(copy);
		clean_exit(CLOSED_MAP, &(g->map), NULL, -1);
	}
	if (copy[y][x] == '1' || copy[y][x] == 'F')
		return ;
	if (copy[y][x] == ' ')
	{
		free_copy(copy);
		clean_exit(CLOSED_MAP, &(g->map), NULL, -1);
	}
	copy[y][x] = 'F';
	flood_fill(copy, x + 1, y, g);
	flood_fill(copy, x - 1, y, g);
	flood_fill(copy, x, y + 1, g);
	flood_fill(copy, x, y - 1, g);
}

static char	**copy_map(t_game *g)
{
	int		row;
	char	**copy;

	copy = malloc(sizeof(char *) * (g->map.y + 1));
	if (!copy)
		clean_exit(MALLOC, &(g->map), NULL, -1);
	row = 0;
	while (row < g->map.y)
	{
		copy[row] = ft_strdup(g->map.raw_map[row]);
		row++;
	}
	copy[row] = NULL;
	return (copy);
}

void	ensure_closed_map(t_game *g)
{
	int		row;
	int		col;
	char	**copy;

	copy = copy_map(g);
	row = 0;
	while (row < g->map.y)
	{
		col = 0;
		while (col < g->map.x)
		{
			if (copy[row][col] == '0')
				flood_fill(copy, col, row, g);
			col++;
		}
		row++;
	}
	free_copy(copy);
}