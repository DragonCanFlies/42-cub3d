/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:00:50 by latabagl          #+#    #+#             */
/*   Updated: 2026/03/22 14:27:38 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Ensure the filename ends with .cub
static void	check_filename(char	*filename)
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

/*
** Convert the parsed character map into a 1D integer array
** Access to a tile becomes: row * map->x + col 
*/
static int	create_int_map_array(t_map *map)
{
	int	row;
	int	col;

	map->map_data = malloc(map->x * map->y * sizeof(int));
	if (!map->map_data)
		return (0);
	row = 0;
	while (row < map->y)
	{
		col = 0;
		while (col < map->x)
		{
			if (map->raw_map[row][col] == '1')
				map->map_data[row * map->x + col] = 1;
			else
				map->map_data[row * map->x + col] = 0;
			col++;
		}
		row++;
	}
	return (1);
}

/*
** Parsing entry point
** Checks input file, parses textures and map,
** normalizes map, initializes player data, and ensures map is valid
*/
void	parse_input(int argc, char **argv, t_game *g)
{
	int				fd;
	t_map_flags		map_flags;
	char			*line;

	ft_bzero(&g->map, sizeof(t_map));
	ft_bzero(&map_flags, sizeof(map_flags));
	if (argc != 2)
		handle_error(ARG_NB_ERR);
	check_filename(argv[1]);
	fd = open_file(argv[1]);
	line = parse_textures(&g->map, &map_flags, fd);
	parse_map(&g->map, fd, line);
	normalize_map(&g->map);
	parse_player_data(g);
	ensure_closed_map(g);
	if (!create_int_map_array(&g->map))
		clean_exit(MALLOC, &g->map, line, fd);
}
