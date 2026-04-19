/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:00:41 by latabagl          #+#    #+#             */
/*   Updated: 2026/01/22 18:00:42 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_map_width_height(t_map *map, int *col)
{
	int	i;
	int	len;

	*col = 0;
	i = 0;
	while (map->raw_map[i])
	{
		len = ft_strlen(map->raw_map[i]);
		if (len > 0 && map->raw_map[i][len - 1] == '\n')
		{
			map->raw_map[i][len - 1] = '\0';
			len--;
		}
		if (len > *col)
			*col = len;
		i++;
	}
	map->x = *col;
	map->y = i;
}

static char	*normalize_line(t_map *map, int col,
	int len, char *old_map_line)
{
	int		i;
	char	*new_map_line;

	new_map_line = malloc(col + 1);
	if (!new_map_line)
		clean_exit(MALLOC, map, NULL, -1);
	i = 0;
	while (i < len)
	{
		new_map_line[i] = old_map_line[i];
		i++;
	}
	while (i < col)
	{
		new_map_line[i] = ' ';
		i++;
	}
	new_map_line[i] = '\0';
	return (new_map_line);
}

void	normalize_map(t_map *map)
{
	int		i;
	int		col;
	int		len;
	char	*new_map_line;

	get_map_width_height(map, &col);
	i = 0;
	while (map->raw_map[i])
	{
		len = ft_strlen(map->raw_map[i]);
		if (len > 0 && len < col)
		{
			new_map_line = normalize_line(map, col, len, map->raw_map[i]);
			free(map->raw_map[i]);
			map->raw_map[i] = new_map_line;
		}
		i++;
	}
}
