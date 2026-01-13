/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 21:18:17 by latabagl          #+#    #+#             */
/*   Updated: 2026/01/13 16:29:20 by loasaad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	clean_texture_paths(t_map *config)
{
	if (config->north_path)
		free(config->north_path);
	if (config->south_path)
		free(config->south_path);
	if (config->east_path)
		free(config->east_path);
	if (config->west_path)
		free(config->west_path);
	config->north_path = NULL;
	config->south_path = NULL;
	config->east_path = NULL;
	config->west_path = NULL;
}

void	clean_config(t_map *config)
{
	int	i;

	clean_texture_paths(config);
	if (config->map)
	{
		i = 0;
		while (config->map[i])
		{
			free(config->map[i]);
			i++;
		}
		free(config->map);
		config->map = NULL;
	}
	if (config->map_data)
	{
		free(config->map_data);
		config->map_data = NULL;
	}
}
