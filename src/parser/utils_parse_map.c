
#include "cub3d.h"

// return 1 if line contains only spaces and tabs
int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (!line[i] || line[i] == '\n')
		return (1);
	return (0);
}

// if EOF after skipping lines, then map is missing
char	*skip_empty_lines(t_map *config, int fd, char *line)
{
	while (line && is_empty_line(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	if (!line)
		clean_exit(NO_MAP, config, line, fd);
	return (line);
}

// map line must contain only authorized characters: space, 0, 1, N/S/W/E
int	has_valid_characters(char *line, int *player_found)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'N'
			|| line[i] == 'S'
			|| line[i] == 'E'
			|| line[i] == 'W')
			(*player_found)++;
		else if (line[i] == ' '
			|| line[i] == '1'
			|| line[i] == '0'
			|| line[i] == '\n'
			|| line[i] == 'G'	//bonus
			|| line[i] == 'F'	//bonus
			|| line[i] == '.'	//bonus
		)
			;
		else
			return (0);
		i++;
	}
	return (1);
}
