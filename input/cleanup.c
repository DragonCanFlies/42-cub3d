/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 21:18:17 by latabagl          #+#    #+#             */
/*   Updated: 2026/01/09 19:33:28 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static void	clean_texture_paths(t_config *config)
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

void	clean_config(t_config *config)
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
