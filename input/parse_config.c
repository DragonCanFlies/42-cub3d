/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:15:51 by latabagl          #+#    #+#             */
/*   Updated: 2026/01/11 19:00:16 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

// return 1 if filename ends with .cub
static void	filename_ends_with_cub(char	*filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		handle_error(INVALID_FILENAME);
	if (!(filename[len - 4] == '.'
			&& filename[len - 3] == 'c'
			&& filename[len - 2] == 'u'
			&& filename[len - 1] == 'b'))
		handle_error(INVALID_FILENAME);
}

static int	open_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		handle_error(OPEN_MAP);
	return (fd);
}

static int	create_int_map_array(t_config *config)
{
	int	row;
	int	col;

	config->map_data = malloc(config->map_x * config->map_y * sizeof(int));
	if (!config->map_data)
		return (0);
	row = 0;
	while (row < config->map_y)
	{
		col = 0;
		while (col < config->map_x)
		{
			if (config->map[row][col] == '1')
				config->map_data[row * config->map_x + col] = 1;
			else
				config->map_data[row * config->map_x + col] = 0;
			col++;
		}
		row++;
	}
	return (1);
}

/* Inside main :
	t_config	config;

	parse_config(argc, argv, &config);
	clean_config(&config);*/
void	parse_config(int argc, char **argv, t_config *config)
{
	int				fd;
	t_config_flags	config_flags;
	char			*line;

	ft_bzero(&config_flags, sizeof(config_flags));
	ft_bzero(config, sizeof(*config));
	if (argc != 2)
		handle_error(ARG_NB_ERR);
	filename_ends_with_cub(argv[1]);
	fd = open_file(argv[1]);
	line = extract_walls_floor_ceiling(config, &config_flags, fd);
	parse_map(config, fd, line);
	normalize_map(config);
	get_player_data(config);
	// TODO check map is enclosed by wall
	if (!create_int_map_array(config))
		clean_exit(MALLOC, config, line, fd);
	// TODO tests and memory leaks
}
