/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:18:03 by latabagl          #+#    #+#             */
/*   Updated: 2026/01/09 16:05:09 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static void	get_map_width_height(t_config *config, int *cols)
{
	int	i;
	int	len;

	*cols = 0;
	i = 0;
	while (config->map[i])
	{
		len = ft_strlen(config->map[i]);
		if (len > 0 && config->map[i][len - 1] == '\n')
		{
			config->map[i][len - 1] = '\0';
			len--;
		}
		if (len > *cols)
			*cols = len;
		i++;
	}
	config->map_x = *cols;
	config->map_y = i;
}

static char	*normalize_line(t_config *config, int cols,
	int len, char *old_map_line)
{
	int		i;
	char	*new_map_line;

	new_map_line = malloc(cols + 1);
	if (!new_map_line)
		clean_exit(MALLOC, config, NULL, -1);
	i = 0;
	while (i < len)
	{
		new_map_line[i] = old_map_line[i];
		i++;
	}
	while (i < cols)
	{
		new_map_line[i] = ' ';
		i++;
	}
	new_map_line[i] = '\0';
	return (new_map_line);
}

void	normalize_map(t_config *config)
{
	int		i;
	int		cols;
	int		len;
	char	*new_map_line;

	get_map_width_height(config, &cols);
	i = 0;
	while (config->map[i])
	{
		len = ft_strlen(config->map[i]);
		if (len > 0 && len < cols)
		{
			new_map_line = normalize_line(config, cols, len, config->map[i]);
			free(config->map[i]);
			config->map[i] = new_map_line;
		}
		i++;
	}
}
