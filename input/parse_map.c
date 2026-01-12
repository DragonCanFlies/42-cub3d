/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 23:13:27 by latabagl          #+#    #+#             */
/*   Updated: 2026/01/09 17:20:50 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

// no empty line inside the map, only valid characters
static void	parse_map_row(t_config *config, int fd,
	char *line, int *player_found)
{
	if (is_empty_line(line))
		clean_exit(EMPTY_LINE_IN_MAP, config, line, fd);
	if (!has_valid_characters(line, player_found))
		clean_exit(INVALID_CHAR_MAP, config, line, fd);
	if (*player_found > 1)
		clean_exit(ONLY_ONE_PLAYER, config, line, fd);
}

// add next map row to config->map
static void	add_row_to_map(t_config *config, int fd, char *line, int rows)
{
	char	**tmp;
	int		i;

	tmp = malloc(sizeof(char *) * (rows + 2));
	if (!tmp)
		clean_exit(MALLOC, config, line, fd);
	i = 0;
	while (i < rows)
	{
		tmp[i] = config->map[i];
		i++;
	}
	tmp[rows] = line;
	tmp[rows + 1] = NULL;
	free(config->map);
	config->map = tmp;
}

// store the map inside config->map
void	parse_map(t_config *config, int fd, char *line)
{
	int		rows;
	int		player_found;

	player_found = 0;
	rows = 0;
	line = skip_empty_lines(config, fd, line);
	while (line)
	{
		parse_map_row(config, fd, line, &player_found);
		add_row_to_map(config, fd, line, rows);
		rows++;
		line = get_next_line(fd);
	}
	if (player_found != 1)
		clean_exit(NO_PLAYER, config, line, fd);
	close(fd);
}
