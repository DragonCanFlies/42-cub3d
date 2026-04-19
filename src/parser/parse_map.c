/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:01:06 by latabagl          #+#    #+#             */
/*   Updated: 2026/03/22 16:15:59 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// add next map row to map->raw_map
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
