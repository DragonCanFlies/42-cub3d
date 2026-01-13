/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 23:13:27 by latabagl          #+#    #+#             */
/*   Updated: 2026/01/13 20:00:00 by loasaad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// add next map row to map->map
static void	add_row_to_map(t_map *map, int fd, char *line, int rows)
{
	char	**tmp;
	int		i;

	tmp = malloc(sizeof(char *) * (rows + 2));
	if (!tmp)
		clean_exit(MALLOC, map, line, fd);
	i = 0;
	while (i < rows)
	{
		tmp[i] = map->raw_map[i];
		i++;
	}
	tmp[rows] = line;
	tmp[rows + 1] = NULL;
	free(map->raw_map);
	map->raw_map = tmp;
}

// no empty line inside the map, only valid characters
static void	parse_map_row(t_map *map, int fd, char *line, int *player_found)
{
	if (is_empty_line(line))
		clean_exit(EMPTY_LINE_IN_MAP, map, line, fd);
	if (!has_valid_characters(line, player_found))
		clean_exit(INVALID_CHAR_MAP, map, line, fd);
	if (*player_found > 1)
		clean_exit(ONLY_ONE_PLAYER, map, line, fd);
}

// store the map inside map->raw_map
void	parse_map(t_map *map, int fd, char *line)
{
	int		rows;
	int		player_found;

	player_found = 0;
	rows = 0;
	line = skip_empty_lines(map, fd, line);
	while (line)
	{
		parse_map_row(map, fd, line, &player_found);
		add_row_to_map(map, fd, line, rows);
		rows++;
		line = get_next_line(fd);
	}
	if (player_found != 1)
		clean_exit(NO_PLAYER, map, line, fd);
	close(fd);
}
