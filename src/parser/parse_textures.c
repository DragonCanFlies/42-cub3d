#include "cub3d.h"

// Store texture path or RGB color based on identifier type
static void	store_element_data(char *data, char *line, t_map *map, int fd)
{
	if (map->current_id == NO)
		map->north_path = data;
	else if (map->current_id == SO)
		map->south_path = data;
	else if (map->current_id == EA)
		map->east_path = data;
	else if (map->current_id == WE)
		map->west_path = data;
	else if (map->current_id == F)
	{
		if (handle_rgb(map->floor, data) == -1)
			clean_exit(COLOR, map, line, fd);
	}
	else if (map->current_id == C)
	{
		if (handle_rgb(map->ceiling, data) == -1)
			clean_exit(COLOR, map, line, fd);
	}
}

// Extract the value part (texture path or RGB values)
static void	extract_value(char *line, t_map *map, int i, int fd)
{
	int		k;
	char	*value;

	k = i;
	skip_token(line, &i);
	value = ft_substr(line, k, i - k);
	if (!value)
		clean_exit(MALLOC, map, line, fd);
	store_element_data(value, line, map, fd);
	skip_space_or_tab(line, &i);
	if (line[i] && line[i] != '\n')
		clean_exit(EXTRA_INFO, map, line, fd);
}

// Extract and validate the identifier (NO, SO, WE, EA, F, C)
// Returns index where the value starts, or -1 if line is empty
static int	extract_id(char *line, t_map *map, t_map_flags *flags, int fd)
{
	int	i;
	int	j;

	i = 0;
	skip_space_or_tab(line, &i);
	if (!line[i] || line[i] == '\n')
		return (-1);
	j = i;
	skip_token(line, &i);
	map->current_id = get_map_flag(line, i, j, flags);
	if (map->current_id == -1)
		clean_exit_no_msg(map, line, fd);
	skip_space_or_tab(line, &i);
	if (!line[i] || line[i] == '\n')
		clean_exit(NO_INFO, map, line, fd);
	return (i);
}

// Parse one line of texture/color configuration
static void	parse_line(char *line, t_map *map, t_map_flags *flags, int fd)
{
	int		i;

	i = extract_id(line, map, flags, fd);
	if (i == -1)
		return ;
	extract_value(line, map, i, fd);
}

char	*parse_textures(t_map *map, t_map_flags *map_flags, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && !textures_are_extracted(map_flags))
	{
		parse_line(line, map, map_flags, fd);
		free(line);
		line = get_next_line(fd);
	}
	if (!textures_are_extracted(map_flags))
		clean_exit(INCOMPLETE_FILE, map, line, fd);
	return (line);
}
