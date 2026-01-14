/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 21:18:17 by latabagl          #+#    #+#             */
/*   Updated: 2026/01/14 15:23:45 by loasaad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	clean_texture_paths(t_map *map)
{
	if (map->north_path)
		free(map->north_path);
	if (map->south_path)
		free(map->south_path);
	if (map->east_path)
		free(map->east_path);
	if (map->west_path)
		free(map->west_path);
	map->north_path = NULL;
	map->south_path = NULL;
	map->east_path = NULL;
	map->west_path = NULL;
}

void	clean_map(t_map *map)
{
	int	i;

	clean_texture_paths(map);
	if (map->raw_map)
	{
		i = 0;
		while (map->raw_map[i])
		{
			free(map->raw_map[i]);
			i++;
		}
		free(map->raw_map);
		map->raw_map = NULL;
	}
	if (map->map_data)
	{
		free(map->map_data);
		map->map_data = NULL;
	}
}
